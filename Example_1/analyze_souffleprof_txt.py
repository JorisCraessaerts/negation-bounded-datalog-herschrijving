#!/usr/bin/env python3
# analyze_souffleprof_txt.py
# Parseert 'souffleprof' TXT-rapporten (top/relations/rules),
# maakt CSV-samenvattingen, plots en voert niet-parametrische toetsen uit.

import argparse
import re
import os
import sys
from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import mannwhitneyu, kruskal
import scikit_posthocs as sp  # posthoc_dunn via sp.posthoc_dunn

sns.set(context="talk", style="whitegrid")


# ========================= Helpers: parsing =========================

# Flexibele detectie van de top-header (case-insensitive, spaties genegeerd)
TOP_HEADER_RE = re.compile(
    r"runtime\s+loadtime\s+savetime\s+relations\s+rules\s+tuples\s+generated",
    re.I,
)

def split_cols(line: str):
    """
    Splits kolommen op BASIS van >=2 spaties.
    Enkele spaties blijven binnen dezelfde kolom (zoals souffleprof-tabellen).
    """
    return re.split(r"\s{2,}", line.strip())

def parse_time_to_ms(s: str) -> float:
    """
    '14s' -> 14000.0 ms, '.000s' -> 0.0 ms
    """
    if s is None:
        return np.nan
    s = s.strip()
    if not s.endswith("s"):
        return np.nan
    try:
        return float(s[:-1]) * 1000.0
    except ValueError:
        return np.nan

def parse_num_with_suffix(t: str) -> float:
    """
    Converteer '340K', '4.99M', '2_345', '1,234', '500' → float.
    Ondersteunt K (1e3), M (1e6). Onparseerbaar → NaN.
    """
    if t is None:
        return np.nan
    x = str(t).strip()
    if x == "" or x == "-":
        return np.nan
    x = x.replace("_", "").replace(",", "")
    m = re.match(r"^([0-9]*\.?[0-9]+)\s*([KkMm])?$", x)
    if not m:
        try:
            return float(x)
        except Exception:
            return np.nan
    val = float(m.group(1))
    suf = (m.group(2) or "").lower()
    if suf == "k":
        return val * 1_000.0
    if suf == "m":
        return val * 1_000_000.0
    return val

def split_sections(text: str):
    """
    Vindt:
      - 'top' (header + eerstvolgende niet-lege waardenregel)
      - '----- Relation Table -----' blok
      - '----- Rule Table -----' blok
    """
    lines = [ln.rstrip("\n") for ln in text.splitlines()]

    # TOP
    top_header_idx = None
    for i, ln in enumerate(lines):
        if TOP_HEADER_RE.search(ln.strip()):
            top_header_idx = i
            break
    top_lines = []
    if top_header_idx is not None:
        for j in range(top_header_idx + 1, len(lines)):
            if lines[j].strip():
                top_lines = [lines[top_header_idx], lines[j]]
                break

    # Relation block
    rel_start = None
    for i, ln in enumerate(lines):
        if ln.strip().startswith("----- Relation Table -----"):
            rel_start = i
            break
    rel_block = []
    if rel_start is not None:
        for j in range(rel_start, len(lines)):
            if j > rel_start and lines[j].strip().startswith("----- Rule Table -----"):
                break
            rel_block.append(lines[j])

    # Rule block
    rul_start = None
    for i, ln in enumerate(lines):
        if ln.strip().startswith("----- Rule Table -----"):
            rul_start = i
            break
    rul_block = []
    if rul_start is not None:
        for j in range(rul_start, len(lines)):
            rul_block.append(lines[j])

    return {"top_lines": top_lines, "rel_block": rel_block, "rul_block": rul_block}

def parse_top(two_lines: list):
    """
    Header/values splitsen met split_cols (>=2 spaties).
    Verwachte volgorde: runtime, loadtime, savetime, relations, rules, tuples generated
    """
    if len(two_lines) < 2:
        return {}

    header_tokens = split_cols(two_lines[0])
    value_tokens  = split_cols(two_lines[1])

    # Zorg dat 'tuples generated' één label is
    if header_tokens[-2:] == ["tuples", "generated"]:
        header_tokens = header_tokens[:-2] + ["tuples generated"]

    # Soms is er padding; als values één korter is, merge laatste twee tokens
    if len(value_tokens) + 1 == len(header_tokens):
        value_tokens[-2:] = [" ".join(value_tokens[-2:])]

    if len(header_tokens) < 6 or len(value_tokens) < 6:
        return {}

    try:
        runtime_ms = parse_time_to_ms(value_tokens[0])
        load_ms    = parse_time_to_ms(value_tokens[1])
        save_ms    = parse_time_to_ms(value_tokens[2])
        n_rel      = float(value_tokens[3])
        n_rules    = float(value_tokens[4])
        n_tuples   = parse_num_with_suffix(value_tokens[5])
    except Exception:
        return {}

    return {
        "runtime_ms": runtime_ms,
        "load_ms": load_ms,
        "save_ms": save_ms,
        "n_relations": n_rel,
        "n_rules": n_rules,
        "n_tuples": n_tuples,
    }

def parse_relation_table(block_lines: list) -> pd.DataFrame:
    """
    Relation header (gescheiden door >=2 spaties):
      TOT_T  NREC_T  REC_T  COPY_T  LOAD_T  SAVE_T  TUPLES  READS  TUP/s  ID  NAME
    """
    expect = ["rewrite","dataset","variant","run",
              "TOT_T_ms","NREC_T_ms","REC_T_ms","COPY_T_ms","LOAD_T_ms","SAVE_T_ms",
              "TUPLES","READS","TUPS_per_s","ID","NAME"]
    if not block_lines:
        return pd.DataFrame(columns=expect)

    hdr_idx = None
    for i, ln in enumerate(block_lines):
        if "TOT_T" in ln and "TUPLES" in ln and "ID" in ln:
            hdr_idx = i
            break
    if hdr_idx is None:
        return pd.DataFrame(columns=expect)

    rows = []
    for ln in block_lines[hdr_idx + 1:]:
        s = ln.strip()
        if not s or s.startswith("-----"):
            continue
        parts = split_cols(s)
        # Verwacht 11 kolommen; indien meer → merge tot 11 (NAME kan spaties bevatten)
        while len(parts) > 11:
            parts[-2:] = [" ".join(parts[-2:])]
        if len(parts) != 11:
            continue
        row = {
            "TOT_T_ms":   parse_time_to_ms(parts[0]),
            "NREC_T_ms":  parse_time_to_ms(parts[1]),
            "REC_T_ms":   parse_time_to_ms(parts[2]),
            "COPY_T_ms":  parse_time_to_ms(parts[3]),
            "LOAD_T_ms":  parse_time_to_ms(parts[4]),
            "SAVE_T_ms":  parse_time_to_ms(parts[5]),
            "TUPLES":     parse_num_with_suffix(parts[6]),
            "READS":      parse_num_with_suffix(parts[7]),
            "TUPS_per_s": parse_num_with_suffix(parts[8]),
            "ID":         parts[9],
            "NAME":       parts[10],
        }
        rows.append(row)
    df = pd.DataFrame(rows, columns=expect[4:])
    return df

def parse_rule_table(block_lines: list) -> pd.DataFrame:
    """
    Rule header (gescheiden door >=2 spaties):
      TOT_T  NREC_T  REC_T  TUPLES  TUP/s  ID  RELATION
    """
    expect = ["rewrite","dataset","variant","run",
              "TOT_T_ms","NREC_T_ms","REC_T_ms","TUPLES","TUPS_per_s","ID","NAME"]
    if not block_lines:
        return pd.DataFrame(columns=expect)

    hdr_idx = None
    for i, ln in enumerate(block_lines):
        if "TOT_T" in ln and "TUPLES" in ln and "ID" in ln:
            hdr_idx = i
            break
    if hdr_idx is None:
        return pd.DataFrame(columns=expect)

    rows = []
    for ln in block_lines[hdr_idx + 1:]:
        s = ln.strip()
        if not s or s.startswith("-----"):
            continue
        parts = split_cols(s)
        # Verwacht 7 kolommen; indien meer → merge tot 7 (RELATION kan spaties bevatten)
        while len(parts) > 7:
            parts[-2:] = [" ".join(parts[-2:])]
        if len(parts) != 7:
            continue
        row = {
            "TOT_T_ms":   parse_time_to_ms(parts[0]),
            "NREC_T_ms":  parse_time_to_ms(parts[1]),
            "REC_T_ms":   parse_time_to_ms(parts[2]),
            "TUPLES":     parse_num_with_suffix(parts[3]),
            "TUPS_per_s": parse_num_with_suffix(parts[4]),
            "ID":         parts[5],
            "NAME":       parts[6],
        }
        rows.append(row)
    df = pd.DataFrame(rows, columns=expect[4:])
    return df


# ========================= Helpers: meta & statistiek =========================

def parse_filename_meta(p: Path):
    """
    <rewrite>__<dataset>__<variant>__run<idx>.txt
    voorbeeld: 7_original_unfolded__data_5000nodes_0p1density__noopt__run21.txt
    """
    stem = p.stem
    m = re.match(r"(.+?)__(.+?)__([A-Za-z0-9]+)__run(\d+)$", stem)
    if not m:
        parts = stem.split("__")
        rewrite = parts[0]
        dataset = parts[1] if len(parts) > 1 else "unknown"
        variant = parts[2] if len(parts) > 2 else "unknown"
        run = re.findall(r"run(\d+)", stem)
        run = int(run[0]) if run else -1
        return rewrite, dataset, variant, run
    rewrite, dataset, variant, run = m.groups()
    return rewrite, dataset, variant, int(run)

def cliffs_delta(a, b):
    a = np.asarray(a); b = np.asarray(b)
    greater = sum(x > y for x in a for y in b)
    less = sum(x < y for x in a for y in b)
    n = len(a) * len(b)
    return (greater - less) / n if n else np.nan

def rewrite_id(s: str) -> int:
    m = re.match(r"(\d+)_", s)
    return int(m.group(1)) if m else 9999


# ========================= Main =========================

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prof-dir", required=True, help="Map met .txt uit souffleprof")
    ap.add_argument("--out-dir", required=True, help="Outputmap voor CSV's/plots/tests")
    ap.add_argument("--min-runs", type=int, default=5, help="Min aantal runs per groep")
    ap.add_argument("--dataset", default=None, help="Filter op dataset-tag")
    ap.add_argument("--variant", default=None, help="Filter op variant (std/noopt)")
    args = ap.parse_args()

    prof_dir = Path(args.prof_dir)
    out_dir = Path(args.out_dir)
    plots_dir = out_dir / "plots"
    tests_dir = out_dir / "tests"
    out_dir.mkdir(parents=True, exist_ok=True)
    plots_dir.mkdir(parents=True, exist_ok=True)
    tests_dir.mkdir(parents=True, exist_ok=True)

    files = sorted(prof_dir.glob("*.txt"))
    if not files:
        print(f"Geen TXT-profielen in {prof_dir}")
        sys.exit(0)

    rows_runs, rel_frames, rul_frames = [], [], []
    debug_misses = []

    for f in files:
        rewrite, dataset, variant, run = parse_filename_meta(f)
        if args.dataset and dataset != args.dataset:
            continue
        if args.variant and variant != args.variant:
            continue

        txt = f.read_text(encoding="utf-8", errors="ignore")
        sec = split_sections(txt)

        # TOP
        top = parse_top(sec["top_lines"])
        if not top:
            debug_misses.append(f.name)
        else:
            rows_runs.append({
                "rewrite": rewrite, "dataset": dataset, "variant": variant, "run": run, **top
            })

        # RELATIONS
        rel_df = parse_relation_table(sec["rel_block"])
        if not rel_df.empty:
            rel_df.insert(0, "run", run)
            rel_df.insert(0, "variant", variant)
            rel_df.insert(0, "dataset", dataset)
            rel_df.insert(0, "rewrite", rewrite)
            rel_frames.append(rel_df)

        # RULES
        rul_df = parse_rule_table(sec["rul_block"])
        if not rul_df.empty:
            rul_df.insert(0, "run", run)
            rul_df.insert(0, "variant", variant)
            rul_df.insert(0, "dataset", dataset)
            rul_df.insert(0, "rewrite", rewrite)
            rul_frames.append(rul_df)

    if debug_misses:
        (out_dir / "parse_misses.log").write_text(
            "Top-sectie niet gevonden in:\n" + "\n".join(debug_misses),
            encoding="utf-8"
        )

    if not rows_runs:
        print("Geen top-secties gevonden; controleer je TXT-formaat.")
        print(f"Zie eventueel: {out_dir/'parse_misses.log'}")
        sys.exit(1)

    df_runs = pd.DataFrame(rows_runs)
    df_runs["rewrite_id"] = df_runs["rewrite"].map(rewrite_id)
    df_runs.to_csv(out_dir / "runs_summary.csv", index=False)

    df_rel = (pd.concat(rel_frames, ignore_index=True)
              if rel_frames else pd.DataFrame(columns=[
                  "rewrite","dataset","variant","run",
                  "TOT_T_ms","NREC_T_ms","REC_T_ms","COPY_T_ms","LOAD_T_ms","SAVE_T_ms",
                  "TUPLES","READS","TUPS_per_s","ID","NAME"]))
    df_rel.to_csv(out_dir / "relations_raw.csv", index=False)

    df_rul = (pd.concat(rul_frames, ignore_index=True)
              if rul_frames else pd.DataFrame(columns=[
                  "rewrite","dataset","variant","run",
                  "TOT_T_ms","NREC_T_ms","REC_T_ms","TUPLES","TUPS_per_s","ID","NAME"]))
    df_rul.to_csv(out_dir / "rules_raw.csv", index=False)

    # Filter op min-runs
    grp = df_runs.groupby(["dataset","variant","rewrite"])
    valid_keys = [k for k, g in grp if len(g) >= args.min_runs]
    valid_df = pd.DataFrame(valid_keys, columns=["dataset","variant","rewrite"])
    df_runs_v = df_runs.merge(valid_df, on=["dataset","variant","rewrite"], how="inner")

    # Samenvatting per combinatie
    agg = (df_runs_v
           .groupby(["dataset","variant","rewrite","rewrite_id"], as_index=False)
           .agg(n=("runtime_ms","count"),
                median_runtime_ms=("runtime_ms","median"),
                iqr_runtime_ms=("runtime_ms", lambda x: np.subtract(*np.percentile(x, [75, 25]))),
                median_load_ms=("load_ms","median"),
                median_save_ms=("save_ms","median"),
                median_tuples=("n_tuples","median"))
           .sort_values(["dataset","variant","rewrite_id"]))
    agg.to_csv(out_dir / "runtime_cell_summary.csv", index=False)

    # -------------------- Plots --------------------
    for (ds, var), g in df_runs_v.groupby(["dataset","variant"]):
        order = sorted(g["rewrite"].unique(), key=rewrite_id)

        # Boxplot runtime
        plt.figure(figsize=(max(8, 1.2*len(order)), 6))
        ax = sns.boxplot(data=g, x="rewrite", y="runtime_ms", order=order)
        ax.set_title(f"Total runtime per rewrite (dataset={ds}, variant={var})")
        ax.set_xlabel("Rewrite")
        ax.set_ylabel("Runtime (ms)")
        plt.xticks(rotation=30, ha="right")
        plt.tight_layout()
        plt.savefig(out_dir / "plots" / f"box_runtime__{ds}__{var}.png", dpi=150)
        plt.close()

        # Evolutie mediane runtime
        gg = agg[(agg["dataset"] == ds) & (agg["variant"] == var)].sort_values("rewrite_id")
        plt.figure(figsize=(10, 5))
        plt.plot(gg["rewrite_id"], gg["median_runtime_ms"], marker="o")
        plt.xticks(gg["rewrite_id"], gg["rewrite"], rotation=30, ha="right")
        plt.title(f"Median runtime evolution across rewrites (dataset={ds}, variant={var})")
        plt.ylabel("Median runtime (ms)")
        plt.tight_layout()
        plt.savefig(out_dir / "plots" / f"line_median_runtime__{ds}__{var}.png", dpi=150)
        plt.close()

    # Top-5 relations per rewrite (median TOT_T_ms)
    if not df_rel.empty:
        rel_med = (df_rel
                   .groupby(["dataset","variant","rewrite","NAME"], as_index=False)
                   .agg(median_TOT_T_ms=("TOT_T_ms","median")))
        rel_med.to_csv(out_dir / "relations_summary.csv", index=False)
        for (ds, var, rew), g in rel_med.groupby(["dataset","variant","rewrite"]):
            g2 = g.sort_values("median_TOT_T_ms", ascending=False).head(5)
            plt.figure(figsize=(8, 4))
            sns.barplot(data=g2, x="NAME", y="median_TOT_T_ms")
            plt.title(f"Top-5 relations (dataset={ds}, variant={var}, rewrite={rew})")
            plt.ylabel("Median TOT_T (ms)")
            plt.xlabel("Relation")
            plt.xticks(rotation=30, ha="right")
            plt.tight_layout()
            plt.savefig(out_dir / "plots" / f"relations_top5__{ds}__{var}__{rew}.png", dpi=150)
            plt.close()

    # Top rules per rewrite (median TOT_T_ms)
    if not df_rul.empty:
        rul_med = (df_rul
                   .groupby(["dataset","variant","rewrite","NAME"], as_index=False)
                   .agg(median_TOT_T_ms=("TOT_T_ms","median")))
        rul_med.to_csv(out_dir / "rules_summary.csv", index=False)
        for (ds, var, rew), g in rul_med.groupby(["dataset","variant","rewrite"]):
            g2 = g.sort_values("median_TOT_T_ms", ascending=False).head(10)
            plt.figure(figsize=(10, 5))
            sns.barplot(data=g2, x="NAME", y="median_TOT_T_ms")
            plt.title(f"Top rules (dataset={ds}, variant={var}, rewrite={rew})")
            plt.ylabel("Median TOT_T (ms)")
            plt.xlabel("Rule")
            plt.xticks(rotation=45, ha="right")
            plt.tight_layout()
            plt.savefig(out_dir / "plots" / f"rules_top__{ds}__{var}__{rew}.png", dpi=150)
            plt.close()

    # -------------------- Toetsen --------------------
    # Mann–Whitney per rewrite: std vs noopt
    rows_mw = []
    for (ds, rew), g in df_runs_v.groupby(["dataset","rewrite"]):
        variants = set(g["variant"].unique())
        if not {"std","noopt"}.issubset(variants):
            continue
        a = g[g["variant"]=="std"]["runtime_ms"].values
        b = g[g["variant"]=="noopt"]["runtime_ms"].values
        if len(a) >= args.min_runs and len(b) >= args.min_runs:
            U, p = mannwhitneyu(a, b, alternative="two-sided")
            eff = cliffs_delta(a, b)
            rows_mw.append({
                "dataset": ds, "rewrite": rew,
                "n_std": len(a), "n_noopt": len(b),
                "U": U, "p": p, "cliffs_delta": eff
            })
    pd.DataFrame(rows_mw).to_csv(out_dir / "tests" / "std_vs_noopt_mannwhitney.csv", index=False)

    # Kruskal-Wallis over rewrites per (dataset, variant) + Dunn posthoc
    rows_kw = []
    for (ds, var), g in df_runs_v.groupby(["dataset","variant"]):
        groups = [sub["runtime_ms"].values for _, sub in g.groupby("rewrite")]
        labels = [name for name, _ in g.groupby("rewrite")]
        if len(groups) <= 2 or any(len(x) < args.min_runs for x in groups):
            continue
        H, p = kruskal(*groups)
        rows_kw.append({"dataset": ds, "variant": var, "k": len(groups), "H": H, "p": p})
        tmp = g[["rewrite","runtime_ms"]].copy()
        ph = sp.posthoc_dunn(tmp, val_col="runtime_ms", group_col="rewrite", p_adjust="fdr_bh")
        ph.to_csv(out_dir / "tests" / f"dunn_{ds}__{var}.csv")
    pd.DataFrame(rows_kw).to_csv(out_dir / "tests" / "kruskal_over_rewrites.csv", index=False)

    print(f"Klaar. CSV’s in {out_dir}/, figuren in {plots_dir}/, toetsen in {tests_dir}/")
    if debug_misses:
        print(f"⚠ Top-sectie niet gevonden in {len(debug_misses)} bestand(en) → zie {out_dir/'parse_misses.log'}")


if __name__ == "__main__":
    main()
