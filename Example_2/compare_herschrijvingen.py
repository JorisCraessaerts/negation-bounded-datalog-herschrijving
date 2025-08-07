
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

def compare_total_runtimes(directory, output_dir="plots"):
    os.makedirs(output_dir, exist_ok=True)
    data = []

    # Sorteer eerst alle paths op voornummer
    files = sorted(Path(directory).glob("*_data_*_run*.json"), key=lambda p: extract_prefix_number(p.name))

    for file_path in files:
        with open(file_path) as f:
            json_data = json.load(f)

        program_name = "_".join(file_path.stem.split("_data_")[0].split("_"))
        run_id = file_path.stem.split("_run")[-1]
        total_runtime_ns = json_data["root"]["program"]["runtime"]["end"] - json_data["root"]["program"]["runtime"]["start"]
        total_runtime_us = total_runtime_ns

        data.append({
            "Herschrijving": program_name,
            "Run": run_id,
            "Total Runtime (µs)": total_runtime_us
        })

    df = pd.DataFrame(data)
    if df.empty:
        print("Geen benchmarkdata gevonden.")
        return

    # Bewaar sorteervolgorde
    unique_programs = sorted(df["Herschrijving"].unique(), key=extract_prefix_number)
    df["Herschrijving"] = pd.Categorical(df["Herschrijving"], categories=unique_programs, ordered=True)

    # Plot boxplot van total runtime per herschrijving
    plt.figure(figsize=(max(6, len(unique_programs) * 1.5), 6))
    sns.boxplot(data=df, x="Herschrijving", y="Total Runtime (µs)")
    plt.title("Vergelijking van totale runtimes per herschrijving")
    plt.xticks(rotation=30, ha='right')
    plt.tight_layout()
    plt.savefig(Path(output_dir) / "vergelijking_total_runtimes_per_herschrijving.png")
    plt.close()
    print(f"Vergelijkingsplot opgeslagen in: {output_dir}")

compare_total_runtimes("benchmarks")
