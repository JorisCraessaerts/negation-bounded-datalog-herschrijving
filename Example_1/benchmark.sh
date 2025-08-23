#!/bin/bash
# Soufflé benchmarks: compiled STD vs NOOPT, met profiling logs en robuuste mem-limieten.
set -o pipefail

############################ Config ############################

DATASETS=(
  "50 0.02"     # Matige dichtheid
  #  "5000 0.02"
  #  "5000 0.1"
  #  "5000 0.2"
  # "500 0.5"
  # "500 1.0"
)

DATA_TYPE="edge"        # 'edge' | 'rs' | 'blue_red'

TIMEOUT_SECONDS=1000
WARMUP_RUNS=5
BENCHMARK_RUNS=30

MAX_MEM_GB=10            # adresruimte-limiet voor RUNS (GB)
LIMIT_BUILDS=0          # 1 = ook builds limiteren; 0 = builds zonder memlimiet

JOBS=1

FACTS_ROOT="facts"
BIN_DIR="bin_build"
BENCH_DIR="benchmarks"
OUTPUT_DIR="output"

# Variants
VARIANT_STD="std"
VARIANT_NOOPT="noopt"

# Compile flags
BUILD_FLAGS_STD=""  # standaard
BUILD_FLAGS_NOOPT="--magic-transform-exclude='*' --inline-exclude='*'"

# Alle programma's (gesorteerd)
mapfile -t PROGRAMS < <(ls -1 *.dl 2>/dev/null | sort -V)

########################### Helpers ###########################

log_cmd(){ { printf '>> '; printf '%q ' "$@"; printf '\n'; } >&2; }

dataset_tag(){ echo "data_${1}nodes_${2/./p}density"; }

ensure_dataset(){
  local nodes="$1" dens="$2" tag outdir
  tag="$(dataset_tag "$nodes" "$dens")"
  outdir="${FACTS_ROOT}/${tag}"
  if [[ -f "$outdir/edge.facts" || -f "$outdir/R.facts" || -f "$outdir/Blue.facts" ]]; then
    echo "✓ Dataset bestaat al: $outdir"
  else
    mkdir -p "$outdir"
    log_cmd python3 generate_data.py --nodes "$nodes" --density "$dens" --type "$DATA_TYPE" --output_dir "$outdir"
    python3 generate_data.py --nodes "$nodes" --density "$dens" --type "$DATA_TYPE" --output_dir "$outdir" \
      || { echo "FOUT: dataset genereren faalde voor $outdir" >&2; exit 1; }
  fi
}

# Voer een commando uit met een harde geheugenlimiet (prlimit) of fallback (ulimit -v)
memrun(){
  local bytes=$(( MAX_MEM_GB * 1024 * 1024 * 1024 ))
  if command -v prlimit >/dev/null 2>&1; then
    log_cmd prlimit --as="$bytes" -- "$@"
    prlimit --as="$bytes" -- "$@"
  else
    local kb=$(( MAX_MEM_GB * 1024 * 1024 ))
    # log netjes wat we doen
    { printf '>> '; printf '%q ' bash -c "ulimit -v $kb; exec \"\$@\""; printf ' -- '; printf '%q ' "$@"; printf '\n'; } >&2
    ( ulimit -v "$kb"; exec "$@" )
  fi
}

# Bouw geprofileerde binary (-p bij build) zodat runtime -p <file> werkt
build_binary(){
  local prog="$1" variant="$2" base bin flags
  base="${prog%.dl}"
  bin="${BIN_DIR}/${base}__${variant}"
  case "$variant" in
    "$VARIANT_STD")   flags="$BUILD_FLAGS_STD" ;;
    "$VARIANT_NOOPT") flags="$BUILD_FLAGS_NOOPT" ;;
    *) echo "FOUT: onbekende variant: $variant" >&2; return 1 ;;
  esac
  mkdir -p "$BIN_DIR"

  if [[ "$LIMIT_BUILDS" -eq 1 ]]; then
    log_cmd souffle -j "$JOBS" -p /dev/null $flags -o "$bin" "$prog"
    if ! memrun souffle -j "$JOBS" -p /dev/null $flags -o "$bin" "$prog"; then
      echo "!! BUILD FAIL voor $prog ($variant)" >&2; return 1
    fi
  else
    log_cmd souffle -j "$JOBS" -p /dev/null $flags -o "$bin" "$prog"
    if ! souffle -j "$JOBS" -p /dev/null $flags -o "$bin" "$prog"; then
      echo "!! BUILD FAIL voor $prog ($variant)" >&2; return 1
    fi
  fi

  echo "$bin"
}

# Run binaire executable met profiling log; outputs → ./output met prefix
run_binary(){
  local bin="$1" progbase="$2" facts_dir="$3" variant="$4" run_id="$5"
  local tag="${facts_dir##*/}"
  local prefix="${progbase}__${tag}__${variant}__run${run_id}"

  local outdir="__tmp_${prefix}"
  local prof="${BENCH_DIR}/${prefix}.profile"
  mkdir -p "$outdir" "$BENCH_DIR" "$OUTPUT_DIR"

  log_cmd timeout "$TIMEOUT_SECONDS" "$bin" -F "$facts_dir" -D "$outdir" -j "$JOBS" -p "$prof"
  memrun timeout "$TIMEOUT_SECONDS" "$bin" -F "$facts_dir" -D "$outdir" -j "$JOBS" -p "$prof"
  local status=$?
  echo "Exit status: $status"

  if compgen -G "$outdir/*" >/dev/null; then
    for f in "$outdir"/*; do
      mv "$f" "${OUTPUT_DIR}/${prefix}__$(basename "$f")"
    done
  fi
  rm -rf "$outdir"
}

# Ctrl+C / Ctrl+Z → netjes opruimen
cleanup() {
  echo ""
  echo "Benchmark onderbroken. Processen worden opgeruimd..."
  pkill -TERM souffle 2>/dev/null || true
  pkill -f "${BIN_DIR}/" 2>/dev/null || true
  sleep 1
  pkill -KILL souffle 2>/dev/null || true
  pkill -9 -f "${BIN_DIR}/" 2>/dev/null || true
  echo "Benchmarkrun afgebroken"
  exit 1
}
trap cleanup SIGINT SIGTERM

############################# Start ############################

mkdir -p "$FACTS_ROOT" "$BIN_DIR" "$BENCH_DIR" "$OUTPUT_DIR"

# Datasets klaarzetten
for ds in "${DATASETS[@]}"; do
  read -r NODES DENS <<< "$ds"
  ensure_dataset "$NODES" "$DENS"
done

# Programma's checken
if [[ "${#PROGRAMS[@]}" -eq 0 ]]; then
  echo "FOUT: geen .dl bestanden gevonden in $(pwd)" >&2
  exit 1
fi

# Warmup op middelste dataset met program 0 (STD variant)
mid_idx=$(( ( ${#DATASETS[@]} - 1 ) / 2 ))
read -r MID_N MID_D <<< "${DATASETS[$mid_idx]}"
MID_FACTS="${FACTS_ROOT}/$(dataset_tag "$MID_N" "$MID_D")"

echo "================== WARMUP (${WARMUP_RUNS}x) op ${PROGRAMS[0]} @ ${MID_FACTS} =================="
WARMUP_BIN="$(build_binary "${PROGRAMS[0]}" "$VARIANT_STD")" || WARMUP_BIN=""
if [[ -n "$WARMUP_BIN" && -x "$WARMUP_BIN" ]]; then
  for i in $(seq 1 "$WARMUP_RUNS"); do
    local_out="__tmp_warmup"
    mkdir -p "$local_out"
    log_cmd timeout "$TIMEOUT_SECONDS" "$WARMUP_BIN" -F "$MID_FACTS" -D "$local_out" -j "$JOBS"
    memrun timeout "$TIMEOUT_SECONDS" "$WARMUP_BIN" -F "$MID_FACTS" -D "$local_out" -j "$JOBS"
    echo "Exit status: $?"
    rm -rf "$local_out"
  done
else
  echo "Warmup overgeslagen: build faalde voor ${PROGRAMS[0]}"
fi

# Benchmarks: per programma, per dataset, 2 varianten
echo "================== BENCHMARKS =================="
for prog in "${PROGRAMS[@]}"; do
  base="${prog%.dl}"

  BIN_STD="$(build_binary "$prog" "$VARIANT_STD")"     || BIN_STD=""
  BIN_NOOPT="$(build_binary "$prog" "$VARIANT_NOOPT")" || BIN_NOOPT=""

  for ds in "${DATASETS[@]}"; do
    read -r NODES DENS <<< "$ds"
    FACTS_DIR="${FACTS_ROOT}/$(dataset_tag "$NODES" "$DENS")"
    echo "---- ${base} @ ${FACTS_DIR} ----"

    if [[ -n "$BIN_STD" && -x "$BIN_STD" ]]; then
      for run in $(seq 1 "$BENCHMARK_RUNS"); do
        run_binary "$BIN_STD" "$base" "$FACTS_DIR" "$VARIANT_STD" "$run"
      done
    else
      echo "↳ Overgeslagen: build faalde (std) voor $prog"
    fi

    if [[ -n "$BIN_NOOPT" && -x "$BIN_NOOPT" ]]; then
      for run in $(seq 1 "$BENCHMARK_RUNS"); do
        run_binary "$BIN_NOOPT" "$base" "$FACTS_DIR" "$VARIANT_NOOPT" "$run"
      done
    else
      echo "↳ Overgeslagen: build faalde (noopt) voor $prog"
    fi
  done
done

echo "KLAAR. Profiler logs in '${BENCH_DIR}/', outputs in '${OUTPUT_DIR}/', binaries in '${BIN_DIR}/'."
