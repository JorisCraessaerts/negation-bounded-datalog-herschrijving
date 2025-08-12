import os
import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import textwrap
import re

def wrap_labels(labels, width=30):
    return ['\n'.join(textwrap.wrap(label, width)) for label in labels]

def extract_dataset_name(filename):
    match = re.search(r"_data_(.+?)_run", filename)
    return match.group(1) if match else "unknown_dataset"

def annotate_medians(ax, data, x_col, y_col):
    """Annotaties voor medianen zonder decimalen."""
    medians = data.groupby(x_col)[y_col].median()
    for xtick, label in enumerate(ax.get_xticklabels()):
        median_val = int(medians.iloc[xtick])  # afronden op µs
        ax.text(
            xtick, median_val,
            f"{median_val}",
            ha='center', va='bottom',
            fontsize=8, fontweight='bold', color='black',
            backgroundcolor='white'
        )

def analyze_benchmark_files(directory, program_prefix, output_root="plots"):
    # Verzamel bestanden per dataset
    datasets = {}
    for file_path in Path(directory).glob(f"{program_prefix}_data_*_run*.json"):
        dataset_name = extract_dataset_name(file_path.stem)
        datasets.setdefault(dataset_name, []).append(file_path)

    # Verwerk per dataset
    for dataset_name, files in datasets.items():
        data_rules = []
        data_relations = []
        output_dir = Path(output_root) / dataset_name
        os.makedirs(output_dir, exist_ok=True)

        for file_path in files:
            with open(file_path) as f:
                json_data = json.load(f)

            run_id = file_path.stem.split("_run")[-1]
            program_name = "_".join(file_path.stem.split("_data_")[0].split("_"))
            relations = json_data["root"]["program"]["relation"]

            for relation_name, relation_data in relations.items():
                # Relation-level timing
                if "runtime" in relation_data:
                    relation_runtime = relation_data["runtime"]["end"] - relation_data["runtime"]["start"]
                    data_relations.append({
                        "Program": program_name,
                        "Run": run_id,
                        "Relation": relation_name,
                        "Runtime (µs)": relation_runtime
                    })

                # Rule-level timing
                if "non-recursive-rule" in relation_data:
                    for rule, rule_data in relation_data["non-recursive-rule"].items():
                        runtime_us = rule_data["runtime"]["end"] - rule_data["runtime"]["start"]
                        tuples = rule_data.get("num-tuples", None)
                        data_rules.append({
                            "Program": program_name,
                            "Run": run_id,
                            "Relation": relation_name,
                            "Rule": rule.strip(),
                            "RuleWrapped": '\n'.join(textwrap.wrap(rule.strip(), width=60)),
                            "Runtime (µs)": runtime_us,
                            "Tuples": tuples
                        })

        # Maak boxplots per dataset
        df_rules = pd.DataFrame(data_rules)
        df_relations = pd.DataFrame(data_relations)

        if not df_rules.empty:
            n_rules = df_rules["RuleWrapped"].nunique()
            plt.figure(figsize=(max(10, n_rules * 0.8), 6))
            ax = sns.boxplot(data=df_rules, x="RuleWrapped", y="Runtime (µs)")
            plt.title(f"Execution time per rule ({program_prefix}, dataset={dataset_name})")
            plt.xticks(rotation=45, ha='right', fontsize=8)
            annotate_medians(ax, df_rules, "RuleWrapped", "Runtime (µs)")
            plt.tight_layout()
            plt.savefig(output_dir / f"{program_prefix}_rulewise_runtime_boxplot.png")
            plt.close()

        if not df_relations.empty:
            n_relations = df_relations["Relation"].nunique()
            plt.figure(figsize=(max(10, n_relations * 0.8), 6))
            ax = sns.boxplot(data=df_relations, x="Relation", y="Runtime (µs)")
            plt.title(f"Execution time per relation ({program_prefix}, dataset={dataset_name})")
            plt.xticks(rotation=45, ha='right', fontsize=9)
            annotate_medians(ax, df_relations, "Relation", "Runtime (µs)")
            plt.tight_layout()
            plt.savefig(output_dir / f"{program_prefix}_relationwise_runtime_boxplot.png")
            plt.close()

# Run
files_to_analyze = [file.stem for file in Path("").glob("*.dl")]
for file in files_to_analyze:
    analyze_benchmark_files("benchmarks", file)
