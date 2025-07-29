
import os
import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import textwrap

def wrap_labels(labels, width=30):
    return ['\n'.join(textwrap.wrap(label, width)) for label in labels]

def analyze_benchmark_files(directory, program_prefix, output_dir="plots"):
    os.makedirs(output_dir, exist_ok=True)
    data = []

    for file_path in Path(directory).glob(f"{program_prefix}_data_*_run*.json"):
        with open(file_path) as f:
            json_data = json.load(f)

        run_id = file_path.stem.split("_run")[-1]
        program_name = "_".join(file_path.stem.split("_data_")[0].split("_"))
        relations = json_data["root"]["program"]["relation"]

        for relation_name, relation_data in relations.items():
            if "non-recursive-rule" in relation_data:
                for rule, rule_data in relation_data["non-recursive-rule"].items():
                    runtime_us = rule_data["runtime"]["end"] - rule_data["runtime"]["start"]  # microseconds
                    tuples = rule_data.get("num-tuples", None)
                    data.append({
                        "Program": program_name,
                        "Run": run_id,
                        "Relation": relation_name,
                        "Rule": rule.strip(),
                        "RuleWrapped": '\n'.join(textwrap.wrap(rule.strip(), width=60)),
                        "Runtime (µs)": runtime_us,
                        "Tuples": tuples
                    })

    df = pd.DataFrame(data)

    if df.empty:
        print("⚠️ No matching benchmark data found.")
        return

    # Bewaar CSV
    # df.to_csv(Path(output_dir) / f"{program_prefix}_summary.csv", index=False)

    # Boxplot: execution time per rule (over alle runs heen)
    n_rules = df["RuleWrapped"].nunique()
    plt.figure(figsize=(max(10, n_rules * 0.8), 6))
    sns.boxplot(data=df, x="RuleWrapped", y="Runtime (µs)")
    plt.title(f"Execution time per rule across runs ({program_prefix})")
    plt.xticks(rotation=45, ha='right', fontsize=8)
    plt.tight_layout()
    output_path = Path(output_dir) / f"{program_prefix}_rulewise_runtime_boxplot.png"
    plt.savefig(output_path)
    plt.close()

    print(f"✅ Rule-wise boxplot generated for '{program_prefix}' at {output_path}")

files_to_analyze = [file.stem for file in Path("").glob("*.dl")]

for file in files_to_analyze:
    analyze_benchmark_files("benchmarks", file)


# for file in files_to_analyze:
#     print(file)
#     analyze_benchmark_files("benchmarks", "0_origineel_programma_bounded_negation_voor_herschrijving")


