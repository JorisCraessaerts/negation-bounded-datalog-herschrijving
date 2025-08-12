import os
import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import re

def extract_prefix_number(filename):
    match = re.match(r"(\d+)_", filename)
    return int(match.group(1)) if match else float('inf')

def extract_dataset_name(filename):
    match = re.search(r"_data_(.+?)_run", filename)
    return match.group(1) if match else "unknown_dataset"

def wrap_labels_short(labels, max_len=5):
    return [label if len(label) <= max_len else label[:max_len] + '...' for label in labels]

def annotate_medians(ax, data, x_col, y_col):
    """Medianen toevoegen, afgerond op hele µs (geen decimalen)."""
    medians = data.groupby(x_col)[y_col].median()
    for xtick, label in enumerate(ax.get_xticklabels()):
        median_val = int(medians.iloc[xtick])  # afronden naar int
        ax.text(
            xtick, median_val,
            f"{median_val}",
            ha='center', va='bottom',
            fontsize=8, fontweight='bold', color='black',
            backgroundcolor='white'
        )

def compare_total_runtimes(directory, output_root="plots"):
    files = sorted(Path(directory).glob("*_data_*_run*.json"), key=lambda p: extract_prefix_number(p.name))
    if not files:
        print("Geen benchmarkdata gevonden.")
        return

    datasets = {}
    for file_path in files:
        dataset_name = extract_dataset_name(file_path.stem)
        datasets.setdefault(dataset_name, []).append(file_path)

    for dataset_name, dataset_files in datasets.items():
        data = []
        output_dir = Path(output_root) / dataset_name
        os.makedirs(output_dir, exist_ok=True)

        for file_path in dataset_files:
            with open(file_path) as f:
                json_data = json.load(f)

            program_name = "_".join(file_path.stem.split("_data_")[0].split("_"))
            run_id = file_path.stem.split("_run")[-1]
            total_runtime_us = json_data["root"]["program"]["runtime"]["end"] - json_data["root"]["program"]["runtime"]["start"]

            data.append({
                "Herschrijving": program_name,
                "Run": run_id,
                "Total Runtime (µs)": total_runtime_us
            })

        df = pd.DataFrame(data)
        df["HerschrijvingShort"] = wrap_labels_short(df["Herschrijving"])
        unique_programs = sorted(df["HerschrijvingShort"].unique(), key=lambda p: extract_prefix_number(p))
        df["HerschrijvingShort"] = pd.Categorical(df["HerschrijvingShort"], categories=unique_programs, ordered=True)

        plt.figure(figsize=(max(6, len(unique_programs) * 1.5), 6))
        ax = sns.boxplot(data=df, x="HerschrijvingShort", y="Total Runtime (µs)")
        plt.title(f"Vergelijking totale runtimes ({dataset_name})")
        plt.xticks(rotation=30, ha='right')
        annotate_medians(ax, df, "HerschrijvingShort", "Total Runtime (µs)")
        plt.tight_layout()
        plt.savefig(output_dir / "vergelijking_total_runtimes_per_herschrijving.png")
        plt.close()

compare_total_runtimes("benchmarks")
