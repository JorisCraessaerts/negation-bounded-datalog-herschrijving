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
    "1000 0.01"
)
TIMEOUT_SECONDS=
# --- EINDE CONFIGURATIE ---

echo "Starten van de volledige benchmark-cyclus (met .log en .html generatie)..."

# Loop over elke projectmap
for project_config in "${PROJECT_DIRS[@]}"; do
    IFS=':' read -r project_dir data_type <<< "$project_config"

    if [ ! -d "$project_dir" ]; then
        echo "Projectmap '$project_dir' niet gevonden, wordt overgeslagen."
        continue
    fi

    echo ""
    echo "============================================================"
    echo "Project: $project_dir"
    echo "============================================================"

    mapfile -t programs < <(find "$project_dir" -maxdepth 1 -name "*.dl" | sort)
    if [ ${#programs[@]} -eq 0 ]; then
        echo "Geen .dl-bestanden gevonden in '$project_dir', wordt overgeslagen."
        continue
    fi
    
    facts_base_dir="$project_dir/facts"
    output_base_dir="$project_dir/output"
    benchmarks_base_dir="$project_dir/benchmarks"

    # Loop over elke dataset-configuratie
    for dataset_config in "${DATASETS[@]}"; do
        read -r nodes density <<< "$dataset_config"
        
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir_for_run="${facts_base_dir}/${dataset_name}"

        echo ""
        echo "Verwerken van dataset: $dataset_name"
        echo "------------------------------------------------------------"

        if [ ! -d "$facts_dir_for_run" ]; then
            echo "  -> Data niet gevonden. Genereren van nieuwe data in '$facts_dir_for_run'..."
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir_for_run"
        else
            echo "  -> Data reeds gevonden. Hergebruiken van bestaande data uit '$facts_dir_for_run'."
        fi

        # Loop over elk gevonden programma
        for program_path in "${programs[@]}"; do
            program_name=$(basename "$program_path" .dl)
            
            output_run_dir="${output_base_dir}/${program_name}/${dataset_name}"
            benchmark_run_dir="${benchmarks_base_dir}/${program_name}/${dataset_name}"
            
            # Definieer nu zowel het .log als het .html bestand
            log_file="${benchmark_run_dir}/profile_report.log"
            html_file="${benchmark_run_dir}/profile_report.html"

            echo "  -> Benchmarken van '$program_name'..."
            
            mkdir -p "$output_run_dir" "$benchmark_run_dir"
            
            # Stap 3: Voer Soufflé uit en genereer het .log bestand
            if timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir_for_run" -D "$output_run_dir" -p "$log_file" "$program_path"; then
                echo "     ✅ Soufflé voltooid. Logbestand aangemaakt in '$log_file'."
                
                # # Stap 4: Genereer het HTML rapport van het logbestand
                # if souffleprof -o "$html_file" "$log_file" > /dev/null 2>&1; then
                #     echo "     HTML-rapport aangemaakt in '$html_file'."
                # else
                #     echo "     Kon geen HTML-rapport genereren van het logbestand."
                # fi

            else
                exit_status=$?
                if [ $exit_status -eq 124 ]; then
                    echo "   TIMEOUT: Uitvoering duurde langer dan $TIMEOUT_SECONDS seconden en is gestopt."
                else
                    echo "   FOUT: Soufflé eindigde met een fout (exit code: $exit_status)."
                fi
            fi
        done
    done
done

echo ""
echo "Alle benchmarks zijn voltooid!"