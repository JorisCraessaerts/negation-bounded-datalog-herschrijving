#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Analyze Soufflé JSON profiles (one JSON per run) and produce:
- tidy CSVs: runs.csv, relations.csv, rules.csv
- plots: total runtime by rewrite (per dataset & variant), medians, and relation breakdown
- optional statistical tests across rewrites and between std vs noopt

Usage:
  python analyze_benchmarks_json.py \
	  --bench-dir ./benchmarks \
	  --out-dir ./analysis_json \
	  --min-runs 5 \
	  --run-tests

The script expects filenames like:
  <program_name>__data_<dataset>__<variant>__run<id>.json
e.g.
  3_unfolding__data_5000nodes_0p1density__noopt__run24.json
"""

import argparse
import json
import math
import os
import re
from pathlib import Path
from typing import Any, Dict, List, Tuple, Optional

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# seaborn is optional (nice styles); plots still render with pure matplotlib if missing
try:
	import seaborn as sns
	_HAS_SNS = True
except Exception:
	_HAS_SNS = False

# Optional posthocs for non-parametric multiple comparisons
try:
	import scikit_posthocs as sp
	_HAS_SCPH = True
except Exception:
	_HAS_SCPH = False

# Optional stats
try:
	from scipy import stats
	_HAS_SCIPY = True
except Exception:
	_HAS_SCIPY = False


# --------------------------- filename parsing ---------------------------

FNAME_RE = re.compile(
	r"""^(?P<program>.+?)__data_(?P<dataset>.+?)__(?P<variant>std|noopt)__(?:run)?(?P<run>\d+)$""",
	re.IGNORECASE,
)

def parse_filename(stem: str) -> Optional[Dict[str, Any]]:
	m = FNAME_RE.match(stem)
	if not m:
		return None
	d = m.groupdict()
	d["run"] = int(d["run"])
	# extract numeric prefix as rewrite_id for ordering
	m2 = re.match(r"(?P<id>\d+)_", d["program"])
	d["rewrite_id"] = int(m2.group("id")) if m2 else 999999
	return d


# ------------------------- JSON safe access helpers ---------------------

def duration_us(obj: Optional[Dict[str, Any]]) -> Optional[int]:
	"""Return end-start if both present; else None."""
	if not isinstance(obj, dict):
		return None
	s = obj.get("start")
	e = obj.get("end")
	if isinstance(s, int) and isinstance(e, int):
		return e - s
	return None

def max_usage_rss_kb(root_program: Dict[str, Any]) -> Optional[int]:
	"""Peak RSS from usage.timepoint[*].maxRSS if present; else max of relation maxRSS.post."""
	usage = root_program.get("usage", {})
	tps = usage.get("timepoint", {})
	peak = None
	if isinstance(tps, dict) and tps:
		for _, v in tps.items():
			m = v.get("maxRSS")
			if isinstance(m, int):
				peak = m if peak is None else max(peak, m)
	# Fallback: scan relations maxRSS.post
	if peak is None:
		rels = root_program.get("relation", {})
		if isinstance(rels, dict):
			for _, rv in rels.items():
				maxrss = rv.get("maxRSS", {})
				post = maxrss.get("post")
				if isinstance(post, int):
					peak = post if peak is None else max(peak, post)
	return peak

def to_ms(us: Optional[int]) -> Optional[float]:
	return None if us is None else us / 1000.0

def to_s(us: Optional[int]) -> Optional[float]:
	return None if us is None else us / 1_000_000.0


# ------------------------------- parsing --------------------------------

def parse_profile_file(path: Path) -> Optional[Dict[str, pd.DataFrame]]:
	"""Return dict with 'run','relations','rules' DataFrames for a single JSON."""
	meta = parse_filename(path.stem)
	if not meta:
		return None

	with open(path, "r") as f:
		data = json.load(f)

	prog = data.get("root", {}).get("program", {})
	total_us = duration_us(prog.get("runtime"))  # program total runtime
	peak_kb = max_usage_rss_kb(prog)

	# base row for runs
	df_run = pd.DataFrame([{
		"program": meta["program"],
		"rewrite_id": meta["rewrite_id"],
		"dataset": meta["dataset"],
		"variant": meta["variant"],
		"run": meta["run"],
		"total_runtime_ms": to_ms(total_us),
		"total_runtime_s": to_s(total_us),
		"peak_rss_kb": peak_kb
	}])

	# relations
	rel_rows = []
	rels = prog.get("relation", {})
	if isinstance(rels, dict):
		for rel_name, rel_obj in rels.items():
			rel_rt = to_ms(duration_us(rel_obj.get("runtime")))
			load_ms = to_ms(duration_us(rel_obj.get("loadtime")))
			save_ms = to_ms(duration_us(rel_obj.get("savetime")))
			num_tuples = rel_obj.get("num-tuples")
			source = rel_obj.get("source-locator")

			rel_rows.append({
				"program": meta["program"],
				"rewrite_id": meta["rewrite_id"],
				"dataset": meta["dataset"],
				"variant": meta["variant"],
				"run": meta["run"],
				"relation": rel_name,
				"rel_runtime_ms": rel_rt,
				"rel_load_ms": load_ms,
				"rel_save_ms": save_ms,
				"rel_num_tuples": num_tuples,
				"rel_source": source,
			})

	df_rel = pd.DataFrame(rel_rows) if rel_rows else pd.DataFrame(
		columns=["program","rewrite_id","dataset","variant","run",
				 "relation","rel_runtime_ms","rel_load_ms","rel_save_ms",
				 "rel_num_tuples","rel_source"]
	)

	# rules (non-recursive and recursive if present)
	rule_rows = []
	if isinstance(rels, dict):
		for rel_name, rel_obj in rels.items():
			for kind in ("non-recursive-rule", "recursive-rule"):
				rules = rel_obj.get(kind, {})
				if not isinstance(rules, dict):
					continue
				for rule_str, r_obj in rules.items():
					r_us = duration_us(r_obj.get("runtime"))
					rule_rows.append({
						"program": meta["program"],
						"rewrite_id": meta["rewrite_id"],
						"dataset": meta["dataset"],
						"variant": meta["variant"],
						"run": meta["run"],
						"relation": rel_name,
						"rule_kind": kind,
						"rule": rule_str,
						"rule_runtime_ms": to_ms(r_us),
						"rule_num_tuples": r_obj.get("num-tuples"),
						"rule_source": r_obj.get("source-locator"),
					})

	df_rules = pd.DataFrame(rule_rows) if rule_rows else pd.DataFrame(
		columns=["program","rewrite_id","dataset","variant","run",
				 "relation","rule_kind","rule","rule_runtime_ms","rule_num_tuples","rule_source"]
	)

	return {"run": df_run, "relations": df_rel, "rules": df_rules}


# ------------------------------- plotting --------------------------------

def _maybe_set_style():
	# Smaller fonts so long labels fit; neutral grid.
	plt.rcParams.update({
		"axes.titlesize": 10,   # (we're not using titles now, but keep size small if added later)
		"axes.labelsize": 9,
		"xtick.labelsize": 8,
		"ytick.labelsize": 8,
		"legend.fontsize": 8,
		"figure.dpi": 150,
	})
	if _HAS_SNS:
		sns.set_context("paper")
		sns.set_style("whitegrid")

def order_by_rewrite(df: pd.DataFrame, col="program") -> List[str]:
	tmp = df[[col, "rewrite_id"]].drop_duplicates()
	tmp = tmp.sort_values("rewrite_id", kind="stable")
	return tmp[col].tolist()

def _finalize_and_save(out_path: Path, bottom_pad: float = 0.30, right_pad: float = 0.96):
	# make sure nothing gets clipped and the legend outside is included
	plt.margins(x=0.01)
	# Slight manual padding then tight bbox on save.
	plt.gcf().subplots_adjust(
		bottom=min(0.48, bottom_pad),
		top=0.98,
		right=right_pad,
		left=0.10,
	)
	plt.tight_layout(pad=0.4)
	plt.savefig(out_path, dpi=200, bbox_inches="tight", pad_inches=0.2, facecolor="white")
	plt.close()

def _program_to_vlabel(name: str, rid: Optional[int]) -> str:
	"""Maak 'v<nummer>' uit de programnaam (numerieke prefix).
	Fallback op rewrite_id als er geen prefix is."""
	m = re.match(r"^(\d+)_", str(name))
	if m:
		return f"v{int(m.group(1))}"
	if rid is not None and not (pd.isna(rid)):
		return f"v{int(rid)}"
	return str(name)


def plot_box_by_rewrite(df_runs: pd.DataFrame, out_dir: Path):
    _maybe_set_style()
    if df_runs.empty:
        return

    for (dataset, variant), sub in df_runs.groupby(["dataset", "variant"], observed=True):
        order = order_by_rewrite(sub, "program")
        sub = sub.copy()
        sub["program"] = pd.Categorical(sub["program"], categories=order, ordered=True)

        label_map = {}
        for p in order:
            rid = sub.loc[sub["program"] == p, "rewrite_id"].iloc[0]
            label_map[p] = _program_to_vlabel(p, rid)
        sub["prog_short"] = sub["program"].map(label_map)

        width = max(7, len(order) * 1.2)
        plt.figure(figsize=(width, 5.2))
        if _HAS_SNS:
            sns.boxplot(data=sub, x="prog_short", y="total_runtime_ms")
        else:
            data = [sub[sub["prog_short"] == label_map[p]]["total_runtime_ms"].dropna().values for p in order]
            ax = plt.gca()
            ax.boxplot(data, labels=[label_map[p] for p in order], showfliers=False)

        # ↓↓↓ NIEUW: y-as bij 0 starten
        plt.ylim(bottom=0)

        plt.ylabel("Total runtime (ms)")
        plt.xticks(rotation=0)
        plt.gcf().subplots_adjust(bottom=0.22, top=0.95, right=0.95)

        out = out_dir / f"box_totalruntime__{dataset}__{variant}.png"
        plt.savefig(out, dpi=150)
        plt.close()



def plot_median_bars(df_runs: pd.DataFrame, out_dir: Path):
    _maybe_set_style()
    if df_runs.empty:
        return

    df = df_runs.copy()
    df["median_ms_grp"] = (
        df.groupby(["dataset", "variant", "program", "rewrite_id"], observed=True)["total_runtime_ms"]
          .transform("median")
    )
    med = (df[["dataset", "variant", "program", "rewrite_id", "median_ms_grp"]]
           .drop_duplicates()
           .rename(columns={"median_ms_grp": "median_ms"})
           .sort_values(["dataset", "variant", "rewrite_id"], kind="stable"))

    for (dataset, variant), sub in med.groupby(["dataset", "variant"], observed=True):
        sub = sub.sort_values("rewrite_id", kind="stable").copy()
        sub["prog_short"] = [
            _program_to_vlabel(p, rid) for p, rid in zip(sub["program"].astype(str), sub["rewrite_id"].astype(int))
        ]
        order_short = sub.sort_values("rewrite_id")["prog_short"].tolist()

        width = max(7, len(sub) * 0.8)
        plt.figure(figsize=(width, 5))
        if _HAS_SNS:
            sns.barplot(data=sub, x="prog_short", y="median_ms", order=order_short)
        else:
            ax = plt.gca()
            ax.bar(sub["prog_short"], sub["median_ms"])

        # ↓↓↓ NIEUW: y-as bij 0 starten
        plt.ylim(bottom=0)

        plt.ylabel("Median runtime (ms)")
        plt.xticks(rotation=0)
        plt.gcf().subplots_adjust(bottom=0.22, top=0.95, right=0.95)

        out = out_dir / f"median_totalruntime__{dataset}__{variant}.png"
        plt.savefig(out, dpi=150)
        plt.close()


def plot_relation_breakdown(df_rel: pd.DataFrame, df_runs: pd.DataFrame, out_dir: Path, top_n: int = 6):
    _maybe_set_style()
    if df_rel.empty or df_runs.empty:
        return

    runs_tmp = df_runs.copy()
    runs_tmp["program_str"] = runs_tmp["program"].astype(str)

    med = (runs_tmp
           .groupby(["dataset", "variant", "program_str", "rewrite_id"], observed=True)["total_runtime_ms"]
           .median()
           .reset_index(name="median_ms"))

    for (dataset, variant), ss in med.groupby(["dataset", "variant"], observed=True):
        ss = ss.sort_values("median_ms", kind="stable").head(top_n)
        if ss.empty:
            continue

        rel_tmp = df_rel.copy()
        rel_tmp["program_str"] = rel_tmp["program"].astype(str)

        sub_rel = rel_tmp.merge(
            ss[["program_str", "rewrite_id"]],
            on=["program_str", "rewrite_id"],
            how="inner"
        )
        if sub_rel.empty:
            continue

        sub_rel["rel_runtime_ms"] = sub_rel["rel_runtime_ms"].fillna(0.0)
        piv = (sub_rel
               .groupby(["program_str", "relation"], observed=True)["rel_runtime_ms"]
               .median()
               .reset_index())

        order_df = ss.sort_values(["rewrite_id", "program_str"], kind="stable")
        progs = order_df["program_str"].tolist()
        prog_ids = order_df["rewrite_id"].tolist()
        x = np.arange(len(progs))
        x_labels = [f"v{rid}" for rid in prog_ids]

        relations = sorted(piv["relation"].unique().tolist())

        width = max(9, len(progs) * 1.1)
        plt.figure(figsize=(width, 5.2))
        bottom = np.zeros(len(progs), dtype=float)

        for rel in relations:
            vals = []
            for p in progs:
                v = piv.loc[(piv["program_str"] == p) & (piv["relation"] == rel), "rel_runtime_ms"]
                vals.append(float(v.values[0]) if len(v) else 0.0)
            plt.bar(x, vals, bottom=bottom, label=rel)
            bottom += np.array(vals, dtype=float)

        # ↓↓↓ NIEUW: y-as bij 0 starten (en klein beetje headroom)
        ymax = float(bottom.max()) if len(bottom) else 0.0
        plt.ylim(bottom=0, top=(ymax * 1.05 if ymax > 0 else 1))

        plt.ylabel("Runtime (ms)")
        plt.xlabel("")
        plt.xticks(x, x_labels, rotation=30, ha="right")
        plt.legend(title="Relation", bbox_to_anchor=(1.02, 1), loc="upper left", borderaxespad=0.)

        out = out_dir / f"relation_breakdown__{dataset}__{variant}.png"
        plt.gcf().subplots_adjust(bottom=min(0.42, 0.20 + 0.02 * len(progs)), right=0.78)
        plt.savefig(out, dpi=150, bbox_inches="tight")
        plt.close()
		

		
# ---------- ADD: memory (peak RSS) boxplots with v<id> labels ----------
def plot_memory_box(df_runs: pd.DataFrame, out_dir: Path):
    if df_runs.empty or "peak_rss_kb" not in df_runs.columns:
        return
    df = df_runs.copy()
    df["peak_rss_mb"] = df["peak_rss_kb"].astype(float) / 1024.0

    def _to_vlabel(prog):
        m = re.match(r"(?P<id>\d+)_", str(prog))
        return f"v{int(m.group('id'))}" if m else str(prog)

    df["vlabel"] = df["program"].astype(str).map(_to_vlabel)

    for (dataset, variant), sub in df.groupby(["dataset","variant"], observed=True):
        order = (sub[["program","vlabel","rewrite_id"]]
                 .drop_duplicates()
                 .sort_values("rewrite_id", kind="stable")["vlabel"].tolist())
        width = max(8, len(order) * 1.2)
        plt.figure(figsize=(width, 5.2))
        ax = plt.gca()
        data = [sub.loc[sub["vlabel"]==v, "peak_rss_mb"].dropna().values for v in order]
        ax.boxplot(data, labels=order, showfliers=True)

        # ↓↓↓ NIEUW: y-as bij 0 starten
        ax.set_ylim(bottom=0)

        ax.set_ylabel("Peak RSS (MB)")
        ax.set_xlabel("")
        plt.xticks(rotation=0, ha="center")
        plt.gcf().subplots_adjust(bottom=min(0.25, 0.12 + 0.02 * len(order)))
        out = out_dir / f"box_peakrss__{dataset}__{variant}.png"
        plt.savefig(out, dpi=150)
        plt.close()






# ------------------------------- statistics ------------------------------

def run_stats(df_runs: pd.DataFrame, out_dir: Path, min_runs:int=5):
	"""Basic stats:
	   - Within each dataset+variant: Kruskal-Wallis across rewrites (if enough runs)
	   - Between variants (std vs noopt): paired Wilcoxon per dataset+rewrite if run ids align,
		 else Mann-Whitney U.
	   Save small summary CSVs.
	"""
	out_dir.mkdir(parents=True, exist_ok=True)
	rows_kw = []
	rows_pair = []

	if not _HAS_SCIPY:
		print("SciPy not available; skipping inferential tests.")
		return

	# Across rewrites (per dataset, per variant)
	for (dataset, variant), sub in df_runs.groupby(["dataset","variant"]):
		# ensure enough observations per rewrite
		groups = []
		labels = []
		for prog, ss in sub.groupby("program"):
			if len(ss) >= min_runs:
				groups.append(ss["total_runtime_ms"].values)
				labels.append(prog)
		if len(groups) >= 2 and all(len(g) >= min_runs for g in groups):
			stat, p = stats.kruskal(*groups)
			rows_kw.append({"dataset": dataset, "variant": variant,
							"k_stat": stat, "p_value": p, "k_groups": len(groups),
							"groups": ",".join(labels)})

			# Optional posthoc Dunn if available
			if _HAS_SCPH:
				# build a long-form for scikit-posthocs
				tmp = sub[sub["program"].isin(labels)][["program","total_runtime_ms"]].copy()
				dunn = sp.posthoc_dunn(tmp, val_col="total_runtime_ms", group_col="program", p_adjust="fdr_bh")
				dunn.to_csv(out_dir / f"posthoc_dunn__{dataset}__{variant}.csv")

	pd.DataFrame(rows_kw).to_csv(out_dir / "kw_across_rewrites.csv", index=False)

	# Between variants per dataset + program: try paired by run id; else unpaired MWU
	for (dataset, program), sub in df_runs.groupby(["dataset","program"]):
		has_std = "std" in sub["variant"].unique()
		has_no = "noopt" in sub["variant"].unique()
		if not (has_std and has_no):
			continue
		A = sub[sub["variant"]=="std"][["run","total_runtime_ms"]].set_index("run")
		B = sub[sub["variant"]=="noopt"][["run","total_runtime_ms"]].set_index("run")
		common = A.index.intersection(B.index)
		method = None
		stat = np.nan
		p = np.nan
		if len(common) >= min_runs:
			method = "wilcoxon"
			try:
				stat, p = stats.wilcoxon(A.loc[common, "total_runtime_ms"], B.loc[common, "total_runtime_ms"])
			except ValueError:
				# fallback if identical values etc.
				method = "sign_test"
				diff = A.loc[common, "total_runtime_ms"] - B.loc[common, "total_runtime_ms"]
				n_pos = (diff > 0).sum(); n_neg = (diff < 0).sum()
				# binomial sign test approximation:
				stat = n_pos
				p = stats.binomtest(k=min(n_pos, n_neg), n=n_pos+n_neg, p=0.5, alternative="two-sided").pvalue
		else:
			# unpaired (independent) samples if both have enough runs
			if len(A) >= min_runs and len(B) >= min_runs:
				method = "mannwhitney"
				stat, p = stats.mannwhitneyu(A["total_runtime_ms"].values, B["total_runtime_ms"].values, alternative="two-sided")

		rows_pair.append({"dataset": dataset, "program": program, "method": method, "stat": stat, "p_value": p,
						  "n_std": len(A), "n_noopt": len(B), "n_paired": len(common)})

	pd.DataFrame(rows_pair).to_csv(out_dir / "between_variants.csv", index=False)
	











# ---------- ADD: effect size helpers (no changes to existing code) ----------

def _epsilon_squared_kw(H: float, k: int, N: int) -> float:
	"""Kruskal–Wallis epsilon squared (ε²)."""
	if N <= 0 or k <= 1:
		return float("nan")
	return max(0.0, min(1.0, (H - (k - 1)) / (N - 1)))

def _cliffs_delta(x, y):
	"""Cliff's delta for two independent samples."""
	import numpy as np
	x = np.asarray(x); y = np.asarray(y)
	n_x = len(x); n_y = len(y)
	if n_x == 0 or n_y == 0:
		return float("nan")
	# O(n log n) version
	x_sorted = np.sort(x)
	y_sorted = np.sort(y)
	i = j = more = less = 0
	while i < n_x and j < n_y:
		if x_sorted[i] > y_sorted[j]:
			less += (n_x - i)
			j += 1
		elif x_sorted[i] < y_sorted[j]:
			more += (n_y - j)
			i += 1
		else:
			# ties: advance both; contributes neither more nor less
			i += 1; j += 1
	delta = (more - less) / (n_x * n_y)
	return float(delta)

def _wilcoxon_r(statistic: float, n_pairs: int) -> float:
	"""Approximate effect size r for Wilcoxon signed-rank using Z ~ W / sqrt(n)."""
	# This is a rough heuristic; SciPy can give exact/approx Z in newer versions.
	if n_pairs <= 0:
		return float("nan")
	return abs(statistic) / math.sqrt(n_pairs)

def _common_language_effect_size(x, y):
	"""P(X>Y): common-language effect size for two independent samples."""
	import numpy as np
	x = np.asarray(x); y = np.asarray(y)
	if len(x) == 0 or len(y) == 0:
		return float("nan")
	# Monte Carlo fast estimate (exact on small)
	# For small, do exact:
	if len(x) * len(y) <= 200000:
		comp = (x.reshape(-1,1) > y.reshape(1,-1)).mean()
		return float(comp)
	# large: sample
	rng = np.random.default_rng(42)
	xs = rng.choice(x, size=20000, replace=True)
	ys = rng.choice(y, size=20000, replace=True)
	return float((xs > ys).mean())



# ---------- ADD: extended stats (keeps existing logic intact) ----------
def run_stats_extended(df_runs: pd.DataFrame, out_dir: Path, min_runs: int = 5):
	"""Produce CSVs with inferential tests + effect sizes (ε², Dunn posthoc, Wilcoxon r, Cliff's δ, CLES)."""
	stats_dir = out_dir / "stats"
	stats_dir.mkdir(parents=True, exist_ok=True)

	try:
		from scipy import stats as _spstats
		has_scipy = True
	except Exception:
		has_scipy = False

	try:
		import scikit_posthocs as sp
		has_sp = True
	except Exception:
		has_sp = False

	# 2.1 Summary table (N, median, mean, sd) — per dataset/variant/program
	summary = (df_runs
			   .groupby(["dataset","variant","program"], observed=True)
			   .agg(n=("total_runtime_ms","count"),
					median_ms=("total_runtime_ms","median"),
					mean_ms=("total_runtime_ms","mean"),
					sd_ms=("total_runtime_ms","std"))
			   .reset_index()
			   .sort_values(["dataset","variant","program"], kind="stable"))
	summary.to_csv(stats_dir / "summary_by_program.csv", index=False)

	if not has_scipy:
		print("SciPy not available; skipping inferential tests.")
		return

	# 2.2 Kruskal–Wallis across rewrites (within dataset+variant)
	rows_kw = []
	for (dataset, variant), sub in df_runs.groupby(["dataset","variant"], observed=True):
		# Min runs per group
		groups = []
		labels = []
		sizes = []
		for prog, ss in sub.groupby("program", observed=True):
			if len(ss) >= min_runs:
				groups.append(ss["total_runtime_ms"].values)
				labels.append(str(prog))
				sizes.append(len(ss))
		if len(groups) >= 2 and all(len(g) >= min_runs for g in groups):
			H, p = _spstats.kruskal(*groups)
			eps2 = _epsilon_squared_kw(H, k=len(groups), N=sum(sizes))
			rows_kw.append({
				"dataset": dataset,
				"variant": variant,
				"k_stat": H,
				"p_value": p,
				"epsilon_squared": eps2,
				"k_groups": len(groups),
				"groups": ",".join(labels)
			})
			# Dunn posthoc
			if has_sp:
				tmp = sub[sub["program"].astype(str).isin(labels)][["program","total_runtime_ms"]].copy()
				dunn = sp.posthoc_dunn(tmp, val_col="total_runtime_ms", group_col="program", p_adjust="fdr_bh")
				dunn.to_csv(stats_dir / f"posthoc_dunn__{dataset}__{variant}.csv")
	pd.DataFrame(rows_kw).to_csv(stats_dir / "kw_across_rewrites.csv", index=False)

	# 2.3 Between variants (std vs noopt) per dataset+program
	rows_pair = []
	for (dataset, program), sub in df_runs.groupby(["dataset","program"], observed=True):
		has_std = "std" in sub["variant"].unique()
		has_no  = "noopt" in sub["variant"].unique()
		if not (has_std and has_no):
			continue

		A = sub[sub["variant"]=="std"][["run","total_runtime_ms"]].set_index("run").sort_index()
		B = sub[sub["variant"]=="noopt"][["run","total_runtime_ms"]].set_index("run").sort_index()

		method = None; stat = float("nan"); p = float("nan")
		eff_r = float("nan"); cliffs = float("nan"); cles = float("nan")
		n_std = len(A); n_no = len(B)

		common = A.index.intersection(B.index)
		if len(common) >= min_runs:
			# Paired
			method = "wilcoxon"
			try:
				stat, p = _spstats.wilcoxon(A.loc[common,"total_runtime_ms"], B.loc[common,"total_runtime_ms"])
			except ValueError:
				# fallback: sign test
				method = "sign_test"
				diffs = A.loc[common,"total_runtime_ms"].values - B.loc[common,"total_runtime_ms"].values
				n_pos = int((diffs > 0).sum()); n_neg = int((diffs < 0).sum())
				stat = n_pos
				p = _spstats.binomtest(k=min(n_pos, n_neg), n=n_pos+n_neg, p=0.5, alternative="two-sided").pvalue
			if method == "wilcoxon":
				eff_r = _wilcoxon_r(stat, len(common))
		else:
			# Unpaired
			if n_std >= min_runs and n_no >= min_runs:
				method = "mannwhitney"
				stat, p = _spstats.mannwhitneyu(A["total_runtime_ms"].values, B["total_runtime_ms"].values, alternative="two-sided")
				cliffs = _cliffs_delta(A["total_runtime_ms"].values, B["total_runtime_ms"].values)
				cles   = _common_language_effect_size(A["total_runtime_ms"].values, B["total_runtime_ms"].values)

		rows_pair.append({
			"dataset": dataset, "program": str(program),
			"method": method, "stat": stat, "p_value": p,
			"n_std": n_std, "n_noopt": n_no, "n_paired": len(common),
			"wilcoxon_r": eff_r, "cliffs_delta": cliffs, "CLES": cles
		})

	pd.DataFrame(rows_pair).to_csv(stats_dir / "between_variants.csv", index=False)




# --------------------------------- main ----------------------------------

def main():
	ap = argparse.ArgumentParser(description="Analyze Soufflé JSON profiles.")
	ap.add_argument("--bench-dir", required=True, help="Directory containing *.json profiles")
	ap.add_argument("--out-dir", required=True, help="Output directory for CSVs and plots")
	ap.add_argument("--min-runs", type=int, default=5, help="Minimum runs per group for tests")
	ap.add_argument("--run-tests", action="store_true", help="Run inferential statistics (SciPy required)")
	args = ap.parse_args()

	bench_dir = Path(args.bench_dir)
	out_dir = Path(args.out_dir)
	out_dir.mkdir(parents=True, exist_ok=True)

	files = sorted(bench_dir.glob("*.json"))
	if not files:
		print(f"No JSON profiles found in {bench_dir}")
		return

	all_runs = []
	all_rels = []
	all_rules = []

	for fp in files:
		parsed = parse_profile_file(fp)
		if not parsed:
			# silently skip files with unexpected names
			continue
		all_runs.append(parsed["run"])
		all_rels.append(parsed["relations"])
		all_rules.append(parsed["rules"])

	if not all_runs:
		print("No valid profiles after parsing filenames. Check naming convention.")
		return

	df_runs = pd.concat(all_runs, ignore_index=True)
	df_rel = pd.concat(all_rels, ignore_index=True) if any(len(x) for x in all_rels) else pd.DataFrame()
	df_rules = pd.concat(all_rules, ignore_index=True) if any(len(x) for x in all_rules) else pd.DataFrame()

	# Order programs by rewrite_id for readability
	prog_order = order_by_rewrite(df_runs, "program")
	df_runs["program"] = pd.Categorical(df_runs["program"], categories=prog_order, ordered=True)
	if not df_rel.empty:
		df_rel["program"] = pd.Categorical(df_rel["program"], categories=prog_order, ordered=True)
	if not df_rules.empty:
		df_rules["program"] = pd.Categorical(df_rules["program"], categories=prog_order, ordered=True)

	# Save tidy data
	df_runs.to_csv(out_dir / "runs.csv", index=False)
	if not df_rel.empty:
		df_rel.to_csv(out_dir / "relations.csv", index=False)
	if not df_rules.empty:
		df_rules.to_csv(out_dir / "rules.csv", index=False)

	# Plots
	plots_dir = out_dir / "plots"
	plots_dir.mkdir(parents=True, exist_ok=True)
	plot_box_by_rewrite(df_runs, plots_dir)
	plot_median_bars(df_runs, plots_dir)
	if not df_rel.empty:
		plot_relation_breakdown(df_rel, df_runs, plots_dir, top_n=6)
		
	run_stats_extended(df_runs, out_dir, min_runs=args.min_runs)
	# Extra plot: memory
	plot_memory_box(df_runs, plots_dir)

	# Stats
	if args.run_tests:
		stats_dir = out_dir / "stats"
		run_stats(df_runs, stats_dir, min_runs=args.min_runs)

	# Small textual summary
	summary = (df_runs
			   .groupby(["dataset","variant","program"], as_index=False)
			   .agg(n=("total_runtime_ms","count"),
					median_ms=("total_runtime_ms","median"),
					mean_ms=("total_runtime_ms","mean"),
					sd_ms=("total_runtime_ms","std")))
	summary = summary.sort_values(["dataset","variant","program"])
	summary.to_csv(out_dir / "summary_by_program.csv", index=False)

	print("Done.")
	print(f"CSV: {out_dir}/runs.csv, relations.csv, rules.csv, summary_by_program.csv")
	print(f"Plots in: {plots_dir}")
	if args.run_tests:
		print(f"Stats in: {out_dir}/stats")

if __name__ == "__main__":
	main()
