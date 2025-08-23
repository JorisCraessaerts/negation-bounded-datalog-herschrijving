#!/usr/bin/env python3
"""
Soufflé benchmark analyzer (robuste versie):
- Leest *.json en *.profile in --bench-dir
- Parse met __-gescheiden tokens (zonder strakke regex)
- Bouwt run- en rule-level tabellen
- Maakt figuren en voert tests uit (als er genoeg replicaten zijn)

Gebruik:
python analyze_benchmarks.py --bench-dir ./benchmarks --out-dir ./analysis --min-runs 5 --log-transform
"""
import argparse
import json
import math
import re
from pathlib import Path

import numpy as np
import pandas as pd
from scipy import stats
import statsmodels.api as sm
import statsmodels.formula.api as smf
import matplotlib.pyplot as plt

# -------------------- Filename parsing (robust) --------------------

def parse_meta_from_filename(path: Path):
	"""
	Verwachte vorm (maar tolerant): 
	  <rewrite_label>__data_<...>__<std|noopt>__run<N>.(json|profile)
	Voorbeeld:
	  0_origineel_programma_bounded_negation_voor_herschrijving__data_5000nodes_0p1density__noopt__run1.json
	"""
	stem = path.stem
	parts = stem.split("__")
	if len(parts) < 4:
		return None

	# 1) rewrite_label = eerste deel; haal numerieke prefix (indien aanwezig)
	rewrite_label = parts[0]
	m = re.match(r"(\d+)_", rewrite_label)
	rewrite_id = int(m.group(1)) if m else None

	# 2) zoek dataset, variant, run
	dataset = None
	variant = None
	run = None
	for p in parts[1:]:
		if p.startswith("data_"):
			dataset = p
		elif p in ("std", "noopt"):
			variant = p
		elif p.startswith("run"):
			try:
				run = int(p.replace("run",""))
			except:
				pass

	if dataset is None or variant is None or run is None:
		# Als dit niet matcht, melden we het bestand maar skippen
		return None

	return {
		"rewrite_id": rewrite_id,
		"rewrite_label": rewrite_label,
		"dataset": dataset,
		"variant": variant,
		"run": run,
		"source_file": path.name,
	}

# -------------------- JSON extractors --------------------

def extract_program_runtime_us(js):
	"""
	Gebruik alleen program-level runtime. Als die ontbreekt, return None.
	"""
	try:
		rt = js["root"]["program"]["runtime"]
		if "start" in rt and "end" in rt and rt["end"] >= rt["start"]:
			return int(rt["end"]) - int(rt["start"])
	except Exception:
		pass
	return None



def iter_maxrss_posts(obj):
	if isinstance(obj, dict):
		if "maxRSS" in obj and isinstance(obj["maxRSS"], dict) and "post" in obj["maxRSS"]:
			v = obj["maxRSS"]["post"]
			if isinstance(v, (int, float)):
				yield int(v)
		for v in obj.values():
			yield from iter_maxrss_posts(v)
	elif isinstance(obj, list):
		for v in obj:
			yield from iter_maxrss_posts(v)

def rules_from_relations(js):
	out = []
	try:
		rels = js["root"]["program"]["relation"]
		if isinstance(rels, dict):
			for rel_name, rel_obj in rels.items():
				for section_key in ("non-recursive-rule", "recursive-rule"):
					if section_key in rel_obj and isinstance(rel_obj[section_key], dict):
						for rule_src, rinfo in rel_obj[section_key].items():
							runtime_us = None
							if "runtime" in rinfo and "start" in rinfo["runtime"] and "end" in rinfo["runtime"]:
								s = rinfo["runtime"]["start"]
								e = rinfo["runtime"]["end"]
								if isinstance(s,(int,float)) and isinstance(e,(int,float)) and e>=s:
									runtime_us = int(e) - int(s)
							num_tuples = rinfo.get("num-tuples", None)
							maxrss_post = None
							if "maxRSS" in rinfo and isinstance(rinfo["maxRSS"], dict) and "post" in rinfo["maxRSS"]:
								v = rinfo["maxRSS"]["post"]
								if isinstance(v,(int,float)):
									maxrss_post = int(v)
							out.append({
								"relation": rel_name,
								"rule_src": rule_src,
								"rule_runtime_us": runtime_us,
								"rule_num_tuples": num_tuples,
								"rule_maxRSS_post": maxrss_post,
							})
	except Exception:
		pass
	return out

# -------------------- Effect sizes & helpers --------------------

def iqr(s: pd.Series):
	s = pd.Series(s).dropna()
	if s.empty: return np.nan
	return float(s.quantile(0.75) - s.quantile(0.25))

def cohens_d(x, y):
	x = pd.Series(x).dropna().astype(float)
	y = pd.Series(y).dropna().astype(float)
	if len(x) < 2 or len(y) < 2:
		return np.nan
	nx, ny = len(x), len(y)
	vx, vy = x.var(ddof=1), y.var(ddof=1)
	s = math.sqrt(((nx-1)*vx + (ny-1)*vy) / (nx + ny - 2)) if (nx+ny-2)>0 else np.nan
	if s == 0 or np.isnan(s): return np.nan
	J = 1 - (3/(4*(nx+ny)-9)) if (nx+ny)>2 else 1
	return ((x.mean() - y.mean()) / s) * J

def cliffs_delta(x, y):
	x = pd.Series(x).dropna().astype(float)
	y = pd.Series(y).dropna().astype(float)
	if len(x)==0 or len(y)==0: return np.nan
	greater = 0
	lesser = 0
	for xi in x:
		greater += (xi > y).sum()
		lesser += (xi < y).sum()
	n = len(x)*len(y)
	return (greater - lesser)/n if n>0 else np.nan

def partial_eta_squared(ss_effect, ss_resid):
	denom = ss_effect + ss_resid
	return float(ss_effect/denom) if denom>0 else np.nan

# -------------------- Plots --------------------

def boxplot_with_medians(ax, groups, values, order_labels, title, ylabel):
	data = [values[groups==g] for g in order_labels]
	ax.boxplot(data, labels=order_labels, showfliers=True)
	medians = [np.nanmedian(values[groups==g]) for g in order_labels]
	ax.plot(range(1, len(order_labels)+1), medians, marker="o")
	ax.set_title(title)
	ax.set_ylabel(ylabel)
	ax.tick_params(axis='x', rotation=30)

# -------------------- Main --------------------

def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--bench-dir", type=str, default="./benchmarks")
	ap.add_argument("--out-dir", type=str, default="./analysis")
	ap.add_argument("--min-runs", type=int, default=5)
	ap.add_argument("--log-transform", action="store_true")
	args = ap.parse_args()

	bench_dir = Path(args.bench_dir)
	out_dir = Path(args.out_dir)
	data_dir = out_dir/"data"
	tables_dir = out_dir/"tables"
	plots_dir = out_dir/"plots"
	for d in (out_dir, data_dir, tables_dir, plots_dir):
		d.mkdir(parents=True, exist_ok=True)

	# --- Read files: *.json and *.profile ---
	files = sorted(list(bench_dir.glob("*.json")) + list(bench_dir.glob("*.profile")))
	if not files:
		print(f"[WARN] Geen json/profile bestanden gevonden in {bench_dir}")
		return

	runs_rows, rules_rows, skipped = [], [], []

	for fp in files:
		meta = parse_meta_from_filename(fp)
		if not meta:
			skipped.append(fp.name)
			continue
		try:
			with open(fp, "r") as f:
				js = json.load(f)
		except Exception as e:
			print(f"[WARN] Kon niet lezen: {fp.name}: {e}")
			continue

		rt_us = extract_program_runtime_us(js)
		if rt_us is None:
			# Skip dit bestand; program-level runtime ontbreekt
			continue
		posts = list(iter_maxrss_posts(js))
		prog_maxrss_kb = max(posts) if posts else None
		prog_maxrss_mb = (prog_maxrss_kb/1024.0) if prog_maxrss_kb is not None else np.nan

		runs_rows.append({
			**meta,
			"program_runtime_us": rt_us,
			"program_runtime_ms": (rt_us/1000.0 if rt_us is not None else np.nan),
			"program_maxRSS_MB": prog_maxrss_mb,
		})

		for r in rules_from_relations(js):
			rules_rows.append({
				**meta,
				**r,
				"rule_runtime_ms": (r["rule_runtime_us"]/1000.0 if r["rule_runtime_us"] is not None else np.nan),
			})

	df_runs = pd.DataFrame(runs_rows)
	df_rules = pd.DataFrame(rules_rows)

	if skipped:
		print("[INFO] Bestanden overgeslagen (niet-herkenbare naam):")
		for s in skipped: print("  -", s)

	if df_runs.empty:
		print("[ERROR] Geen geldige runs geparsed. Check bestandsnamen (verwacht __data_...__std/noopt__runN).")
		return

	# sorteren alleen als kolommen bestaan
	sort_cols = [c for c in ["dataset","variant","rewrite_id","run"] if c in df_runs.columns]
	if sort_cols:
		df_runs.sort_values(sort_cols, inplace=True)

	# Save raw tables
	df_runs.to_csv(data_dir/"df_runs.csv", index=False)
	df_rules.to_csv(data_dir/"df_rules.csv", index=False)

	# --- Descriptive summaries ---
	group_cols = [c for c in ["dataset","variant","rewrite_id","rewrite_label"] if c in df_runs.columns]
	summ = df_runs.groupby(group_cols, dropna=False).agg(
		N=("program_runtime_ms","count"),
		median_ms=("program_runtime_ms","median"),
		iqr_ms=("program_runtime_ms", lambda s: float(s.quantile(0.75) - s.quantile(0.25)) if s.notna().any() else np.nan),
		mean_ms=("program_runtime_ms","mean"),
		sd_ms=("program_runtime_ms","std"),
		min_ms=("program_runtime_ms","min"),
		max_ms=("program_runtime_ms","max"),
		median_maxRSS_MB=("program_maxRSS_MB","median"),
	).reset_index()
	summ.to_csv(tables_dir/"summary_runtime_by_rewrite.csv", index=False)

	# Delta vs baseline per dataset × variant
	deltas = []
	for (dataset, variant), sub in summ.groupby(["dataset","variant"]):
		sub = sub.sort_values("rewrite_id")
		if sub.empty: continue
		base_median = sub.iloc[0]["median_ms"]
		base_label  = sub.iloc[0]["rewrite_label"]
		for _, row in sub.iterrows():
			med = row["median_ms"]
			pct = (med/base_median - 1.0)*100.0 if (base_median and not np.isnan(med)) else np.nan
			deltas.append({
				"dataset": dataset,
				"variant": variant,
				"baseline_rewrite": base_label,
				"rewrite_label": row["rewrite_label"],
				"rewrite_id": row["rewrite_id"],
				"median_ms": med,
				"delta_vs_baseline_pct": pct
			})
	pd.DataFrame(deltas).to_csv(tables_dir/"delta_vs_baseline.csv", index=False)

	# --- Plots per dataset × variant ---
	for (dataset, variant), sub in df_runs.groupby(["dataset","variant"]):
		sub = sub.dropna(subset=["program_runtime_ms"])
		if sub.empty: continue

		# Evolution (median line)
		agg = sub.groupby(["rewrite_id","rewrite_label"], as_index=False)["program_runtime_ms"].median().sort_values("rewrite_id")
		plt.figure(figsize=(10,4))
		plt.plot(agg["rewrite_id"], agg["program_runtime_ms"], marker="o")
		plt.xticks(agg["rewrite_id"], agg["rewrite_label"], rotation=30, ha="right")
		plt.ylabel("Total runtime (ms)")
		plt.title(f"Median runtime per rewrite — {dataset} — {variant}")
		plt.tight_layout()
		plt.savefig(plots_dir/f"runtime_evolution__{dataset}__{variant}.png", dpi=150)
		plt.close()

		# Boxplot per rewrite
		order = agg["rewrite_label"].tolist()
		plt.figure(figsize=(12,5))
		ax = plt.gca()
		groups = sub["rewrite_label"]
		values = sub["program_runtime_ms"]
		boxplot_with_medians(ax, groups.values, values.values, order,
							 f"Runtime distribution per rewrite — {dataset} — {variant}",
							 "Total runtime (ms)")
		plt.tight_layout()
		plt.savefig(plots_dir/f"runtime_box__{dataset}__{variant}.png", dpi=150)
		plt.close()

		# Memory evolution (median maxRSS over runs)
		if "program_maxRSS_MB" in sub.columns:
			agg_mem = sub.groupby(["rewrite_id","rewrite_label"], as_index=False)["program_maxRSS_MB"].median().sort_values("rewrite_id")
			if not agg_mem["program_maxRSS_MB"].isna().all():
				plt.figure(figsize=(10,4))
				plt.plot(agg_mem["rewrite_id"], agg_mem["program_maxRSS_MB"], marker="o")
				plt.xticks(agg_mem["rewrite_id"], agg_mem["rewrite_label"], rotation=30, ha="right")
				plt.ylabel("Max RSS (MB)")
				plt.title(f"Median memory per rewrite — {dataset} — {variant}")
				plt.tight_layout()
				plt.savefig(plots_dir/f"memory_evolution__{dataset}__{variant}.png", dpi=150)
				plt.close()

	# --- Rule-level top-10 ---
	if not df_rules.empty:
		for (dataset, variant, rewrite_label), sub in df_rules.groupby(["dataset","variant","rewrite_label"]):
			agg = sub.groupby(["relation","rule_src"], as_index=False)["rule_runtime_ms"].median()
			agg = agg.dropna(subset=["rule_runtime_ms"]).sort_values("rule_runtime_ms", ascending=False).head(10)
			if agg.empty: continue
			plt.figure(figsize=(10,6))
			ylabels = [f"{r[:60]}..." if r and len(r)>63 else (r or "rule") for r in agg["rule_src"]]
			plt.barh(ylabels, agg["rule_runtime_ms"])
			plt.gca().invert_yaxis()
			plt.xlabel("Median rule runtime (ms)")
			plt.title(f"Top-10 rules — {dataset} — {variant} — {rewrite_label}")
			plt.tight_layout()
			plt.savefig(plots_dir/f"rules_top10__{dataset}__{variant}__{rewrite_label}.png", dpi=150)
			plt.close()

	# --- Inferentiële statistiek ---
	def enough_runs_for_cells(df, min_runs):
		g = df.groupby(["rewrite_label","variant"])["program_runtime_ms"].count()
		return (g >= min_runs).all() if not g.empty else False

	tests_written = 0
	anova_written = 0

	for dataset, sub in df_runs.groupby("dataset"):
		variants = set(sub["variant"].dropna().unique())
		if not {"std","noopt"}.issubset(variants):
			print(f"[INFO] Dataset {dataset}: mis 'std' of 'noopt' → sla variant-tests/ANOVA over.")
			continue

		# std vs noopt per rewrite (zoals gepland)
		rows = []
		for rewrite_label, ss in sub.groupby("rewrite_label"):
			xs = ss.loc[ss["variant"]=="std",  "program_runtime_ms"].dropna()
			ys = ss.loc[ss["variant"]=="noopt","program_runtime_ms"].dropna()
			if len(xs) < args.min_runs or len(ys) < args.min_runs:
				continue
			tval, p_welch = stats.ttest_ind(xs, ys, equal_var=False)
			d = cohens_d(xs, ys)
			try:
				u, p_mwu = stats.mannwhitneyu(xs, ys, alternative="two-sided")
			except ValueError:
				p_mwu = np.nan
			cd = cliffs_delta(xs, ys)
			rows.append({
				"dataset": dataset,
				"rewrite_label": rewrite_label,
				"N_std": len(xs), "N_noopt": len(ys),
				"mean_std_ms": xs.mean(), "mean_noopt_ms": ys.mean(),
				"median_std_ms": xs.median(), "median_noopt_ms": ys.median(),
				"welch_t": tval, "welch_p": p_welch, "cohens_d": d,
				"mwu_p": p_mwu, "cliffs_delta": cd,
				"delta_mean_pct": (xs.mean()/ys.mean()-1.0)*100.0 if ys.mean() else np.nan,
				"delta_median_pct": (xs.median()/ys.median()-1.0)*100.0 if ys.median() else np.nan
			})
		if rows:
			pd.DataFrame(rows).sort_values("rewrite_label").to_csv(
				tables_dir/f"std_vs_noopt_tests__{dataset}.csv", index=False
			)
			tests_written += 1

		# Two-way ANOVA / GLM per dataset: rewrite * opt
		if not enough_runs_for_cells(sub, args.min_runs):
			print(f"[INFO] Dataset {dataset}: onvoldoende runs per cel voor ANOVA (min {args.min_runs}).")
			continue

		an = sub.dropna(subset=["program_runtime_ms","rewrite_label","variant"]).copy()
		an["rewrite"] = an["rewrite_label"].astype("category")
		an["opt"] = an["variant"].astype("category")
		y = np.log(an["program_runtime_ms"]) if args.log_transform else an["program_runtime_ms"]
		an_model_df = pd.DataFrame({"y": y, "rewrite": an["rewrite"], "opt": an["opt"]})
		model = smf.ols("y ~ C(rewrite) * C(opt)", data=an_model_df).fit()
		aov = sm.stats.anova_lm(model, typ=2)
		ss_resid = aov.loc["Residual","sum_sq"]
		aov["partial_eta_sq"] = aov["sum_sq"].apply(lambda ss: partial_eta_squared(ss, ss_resid))
		aov.to_csv(tables_dir/f"anova_two_way__{dataset}.csv")
		anova_written += 1

	print(f"[OK] Klaar. Tests geschreven: std_vs_noopt={tests_written}, anova={anova_written}")

if __name__ == "__main__":
	main()
