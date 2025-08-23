# #!/usr/bin/env bash
# # Run souffleprof (ASCII tabellen) op alle .json profielen in benchmarks/
# # en schrijf resultaten naar benchmarks/souffleprof/*.txt

# BENCH_DIR="./benchmarks"
# OUT_DIR="${BENCH_DIR}/souffleprof"
# mkdir -p "$OUT_DIR"

# for f in "$BENCH_DIR"/*.json; do
#     [ -e "$f" ] || continue
#     base="$(basename "$f" .json)"
#     echo "Processing $f -> $OUT_DIR/${base}.txt"

#     # Start souffleprof in een pseudo-tty, wacht kort, stuur quit
#     script -q -c "bash -c 'sleep 0.2; echo quit' | souffleprof \"$f\"" /dev/null > "$OUT_DIR/${base}.txt"
# done

# echo "Klaar! Alle rapporten staan in $OUT_DIR"


#!/usr/bin/env bash
# Minimalistisch: per JSON-profielbestand drie souffleprof-commando's:
#   -c top  → enkel de eerste 2 lijnen
#   -c rel  → volledige output
#   -c rul  → volledige output
# Output komt in benchmarks/souffleprof/<base>.txt

set -o pipefail

BENCH_DIR="./benchmarks"
OUT_DIR="${BENCH_DIR}/souffleprof"

mkdir -p "$OUT_DIR"

shopt -s nullglob
for f in "$BENCH_DIR"/*.json; do
  base="$(basename "$f" .json)"
  out="${OUT_DIR}/${base}.txt"

  # leeg bestand (of aanmaken)
  : > "$out"

  # TOP: enkel eerste 2 lijnen
  # (kopje met bestandsnaam voor traceerbaarheid)
  {
    souffleprof "$f" -c top | head -n 2
    echo
  } >> "$out"

  # REL: volledige tabel
  {
    souffleprof "$f" -c rel
    echo
  } >> "$out"

  # RUL: volledige tabel
  {
    souffleprof "$f" -c rul
    echo
  } >> "$out"

  echo "OK  → $out"
done

echo "Klaar. Rapporten staan in: ${OUT_DIR}/"
