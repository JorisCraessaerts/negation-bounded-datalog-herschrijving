#!/bin/bash
trap 'echo "❌ Benchmark geannuleerd door gebruiker"; kill 0; exit 1' SIGINT SIGTERM

# --- CONFIGURATIE ---
PROJECT_DIRS=(
    "Example_1:edge"
    "Example_2:rs"
)
DATASETS=(
    "50 0.1"
    "100 0.05"
    "500 0.02"
)
TIMEOUT_SECONDS=120         # Maximale duur van één soufflé-run
WARMUP_RUNS=10              # Aantal warmup-runs
BENCHMARK_RUNS=3            # Aantal benchmark-runs per programma
SOUFFLE_THREADS=8           # Aantal threads dat Soufflé mag gebruiken
CPU_LIMIT=700               # Maximaal % CPU over alle cores (bijv. 700% = 7 cores)
# --- EINDE CONFIGURATIE ---

echo "🚀 Starten van de benchmarks..."

for project_config in "${PROJECT_DIRS[@]}"; do
    IFS=':' read -r project_dir data_type <<< "$project_config"
    
    echo ""
    echo "📁 Projectmap: $project_dir"

    mapfile -t programs < <(find "$project_dir" -maxdepth 1 -name "*.dl" | sort)
    if [ ${#programs[@]} -eq 0 ]; then
        echo "⚠️ Geen Datalog-bestanden gevonden in $project_dir"
        continue
    fi

    facts_base_dir="$project_dir/facts"
    output_base_dir="$project_dir/output"
    benchmark_dir="${project_dir}/benchmarks"
    mkdir -p "$benchmark_dir"

    # --- WARMUP FASE ---
    if [ "$WARMUP_RUNS" -gt 0 ]; then
        echo "🔥 Uitvoeren van $WARMUP_RUNS warmup-runs..."

        middle_index=$(( (${#DATASETS[@]} - 1) / 2 ))
        warmup_dataset_config=${DATASETS[$middle_index]}
        read -r w_nodes w_density <<< "$warmup_dataset_config"
        warmup_dataset="data_${w_nodes}nodes_${w_density//./p}density"
        facts_dir="${facts_base_dir}/${warmup_dataset}"

        if [ ! -d "$facts_dir" ]; then
            echo "   ➤ Genereren van warmup-facts..."
            python3 generate_data.py --nodes "$w_nodes" --density "$w_density" --type "$data_type" --output_dir "$facts_dir"
        else
            echo "   ➤ Warmup-facts gevonden."
        fi

        warmup_program_path="${project_dir}/0_origineel_programma_bounded_negation_voor_herschrijving.dl"
        warmup_program_name=$(basename "$warmup_program_path" .dl)
        output_dir="${output_base_dir}/warmup_${warmup_program_name}/${warmup_dataset}"
        mkdir -p "$output_dir"

        for i in $(seq 1 $WARMUP_RUNS); do
            log_file="${benchmark_dir}/warmup_${warmup_program_name}_${warmup_dataset}_${i}.json"
            run_output="${output_dir}/run_${i}"
            mkdir -p "$run_output"

            echo -n "   🔁 Warmup $i... "
            if timeout "$TIMEOUT_SECONDS" cpulimit -l $CPU_LIMIT -- nice -n 10 \
                souffle -j $SOUFFLE_THREADS -F "$facts_dir" -D "$run_output" -p "$log_file" "$warmup_program_path"
            then
                echo "OK"
            else
                echo "❌ FOUT of TIMEOUT"
            fi
        done
        echo "✅ Warmup voltooid."
    fi

    # --- BENCHMARKS ---
    for dataset_config in "${DATASETS[@]}"; do
        read -r nodes density <<< "$dataset_config"
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir="${facts_base_dir}/${dataset_name}"

        echo "🔹 Dataset: $dataset_name"

        if [ ! -d "$facts_dir" ]; then
            echo "   ➤ Genereren van facts..."
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir"
        else
            echo "   ➤ Facts gevonden."
        fi

        for program_path in "${programs[@]}"; do
            program_name=$(basename "$program_path" .dl)
            output_dir="${output_base_dir}/${program_name}/${dataset_name}"
            mkdir -p "$output_dir"

            echo "   ➤ Programma: $program_name"

            for i in $(seq 1 $BENCHMARK_RUNS); do
                log_file="${benchmark_dir}/${program_name}_${dataset_name}_run${i}.json"
                run_output="${output_dir}/run_${i}"
                mkdir -p "$run_output"

                echo -n "      🚀 Benchmark $i... "
                if timeout "$TIMEOUT_SECONDS" cpulimit -l $CPU_LIMIT -- nice -n 10 \
                    souffle -j $SOUFFLE_THREADS -F "$facts_dir" -D "$run_output" -p "$log_file" "$program_path"
                then
                    echo "OK"
                else
                    echo "❌ FOUT of TIMEOUT"
                fi
            done
        done
    done
done

echo ""
echo "✅ Alle benchmarks zijn afgerond! Resultaten staan in 'benchmarks/' binnen elke projectmap."
