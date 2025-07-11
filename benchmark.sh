#!/bin/bash

# --- CONFIGURATIE ---
PROJECT_DIRS=(
    "Example_1:edge"
    "Example_2:rs"
)
DATASETS=(
    "50 0.1"
    "100 0.05"
    "500 0.02"
    #"1000 0.01"
)
TIMEOUT_SECONDS=10
WARMUP_RUNS=2
BENCHMARK_RUNS=3
# --- EINDE CONFIGURATIE ---

echo "🚀 Starten van de volledige benchmark-cyclus..."

# Loop over elke projectmap
for project_config in "${PROJECT_DIRS[@]}"; do
    IFS=':' read -r project_dir data_type <<< "$project_config"

    if [ ! -d "$project_dir" ]; then
        echo "⚠️ Projectmap '$project_dir' niet gevonden, wordt overgeslagen."
        continue
    fi

    echo ""
    echo "============================================================"
    echo "📁 Project: $project_dir"
    echo "============================================================"

    mapfile -t programs < <(find "$project_dir" -maxdepth 1 -name "*.dl" | sort)
    if [ ${#programs[@]} -eq 0 ]; then
        echo "🤷 Geen .dl-bestanden gevonden in '$project_dir', wordt overgeslagen."
        continue
    fi
    
    facts_base_dir="$project_dir/facts"
    output_base_dir="$project_dir/output"
    benchmarks_base_dir="$project_dir/benchmarks"

    # --- WARMUP FASE (AANGEPAST) ---
    if [ "$WARMUP_RUNS" -gt 0 ]; then
        echo "🔥 Starten van $WARMUP_RUNS warmup runs..."
        
        middle_index=$(( (${#DATASETS[@]} - 1) / 2 ))
        warmup_dataset_config=${DATASETS[$middle_index]}
        read -r nodes density <<< "$warmup_dataset_config"
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir_for_run="${facts_base_dir}/${dataset_name}"

        if [ ! -d "$facts_dir_for_run" ]; then
            echo "   -> Warmup data niet gevonden. Genereren in '$facts_dir_for_run'..."
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir_for_run"
        else
            echo "   -> Warmup data gevonden in '$facts_dir_for_run'."
        fi

        warmup_program_path=${programs[-1]}
        warmup_program_name=$(basename "$warmup_program_path" .dl)
        
        # Aparte mappen voor warmup output en logs
        warmup_output_dir="${output_base_dir}/_warmup/${warmup_program_name}/${dataset_name}"
        warmup_benchmark_dir="${benchmarks_base_dir}/_warmup/${warmup_program_name}/${dataset_name}"
        mkdir -p "$warmup_output_dir" "$warmup_benchmark_dir"

        echo "   (Gebruikt programma: $warmup_program_name, Dataset: $dataset_name)"

        for i in $(seq 1 $WARMUP_RUNS); do
            echo -n "   -> Warmup run $i van de $WARMUP_RUNS..."
            
            log_file="${warmup_benchmark_dir}/warmup_profile_${i}.log"
            html_file="${warmup_benchmark_dir}/warmup_profile_${i}.html"
            output_dir_for_run="${warmup_output_dir}/run_${i}"
            mkdir -p "$output_dir_for_run"

            # Voer warmup uit en genereer logs/output
            if timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir_for_run" -D "$output_dir_for_run" -p "$log_file" "$warmup_program_path"; then
                 echo -n "OK. "
                 souffleprof -o "$html_file" "$log_file" > /dev/null 2>&1
                 echo "Log aangemaakt."
            else
                exit_status=$?
                if [ $exit_status -eq 124 ]; then
                    echo "TIMEOUT"
                else
                    echo "FOUT (exit code: $exit_status)"
                fi
            fi
        done
        echo "✅ Warmup voltooid."
    fi
    
    # --- ECHTE BENCHMARK FASE ---
    for dataset_config in "${DATASETS[@]}"; do
        read -r nodes density <<< "$dataset_config"
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir_for_run="${facts_base_dir}/${dataset_name}"

        echo ""
        echo "📦 Verwerken van dataset: $dataset_name"
        echo "------------------------------------------------------------"

        if [ ! -d "$facts_dir_for_run" ]; then
            echo "  -> 📂 Data niet gevonden. Genereren..."
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir_for_run"
        else
            echo "  -> ✅ Data reeds gevonden."
        fi

        for program_path in "${programs[@]}"; do
            program_name=$(basename "$program_path" .dl)
            
            output_run_base_dir="${output_base_dir}/${program_name}/${dataset_name}"
            benchmark_run_dir="${benchmarks_base_dir}/${program_name}/${dataset_name}"
            
            echo "  -> Benchmarken van '$program_name' ($BENCHMARK_RUNS runs)..."
            mkdir -p "$output_run_base_dir" "$benchmark_run_dir"

            for run_num in $(seq 1 $BENCHMARK_RUNS); do
                echo -n "     -> Run $run_num... "
                
                output_dir_for_this_run="${output_run_base_dir}/run_${run_num}"
                mkdir -p "$output_dir_for_this_run"

                log_file="${benchmark_run_dir}/profile_${run_num}.log"
                html_file="${benchmark_run_dir}/profile_${run_num}.html"
                
                if timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir_for_run" -D "$output_dir_for_this_run" -p "$log_file" "$program_path"; then
                    echo -n "OK. "
                    if souffleprof -o "$html_file" "$log_file" > /dev/null 2>&1; then
                        echo "Log en HTML aangemaakt."
                    else
                        echo "Log aangemaakt, maar HTML-conversie mislukt."
                    fi
                else
                    exit_status=$?
                    if [ $exit_status -eq 124 ]; then
                        echo "TIMEOUT"
                    else
                        echo "FOUT (exit code: $exit_status)"
                    fi
                fi
            done
        done
    done
done

echo ""
echo "🎉 Alle benchmarks zijn voltooid!"