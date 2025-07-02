#!/bin/bash

# --- CONFIGURATIE ---

# Definieer de projectmappen en het type data dat ze nodig hebben.
# Formaat: "MAPNAAM:TYPE"
# TYPE kan 'edge' of 'rs' zijn.
PROJECT_DIRS=(
    "example 1 uit paper:edge"
    "Example 2:rs"
)

# Definieer de datasets die je wilt genereren en testen.
# Formaat: "NODES DENSITY"
DATASETS=(
    "50 0.1"
    "100 0.05"
    "500 0.02"
    "1000 0.01"
)

# Timeout in seconden (5 minuten = 300 seconden)
TIMEOUT_SECONDS=300

# --- EINDE CONFIGURATIE ---

echo "🚀 Starten van de volledige benchmark-cyclus..."

# Loop over elke projectmap
for project_config in "${PROJECT_DIRS[@]}"; do
    # Splits de configuratie op in mapnaam en data-type
    IFS=':' read -r project_dir data_type <<< "$project_config"

    if [ ! -d "$project_dir" ]; then
        echo "⚠️ Projectmap '$project_dir' niet gevonden, wordt overgeslagen."
        continue
    fi

    echo ""
    echo "============================================================"
    echo "📁 Project: $project_dir"
    echo "============================================================"

    # Vind dynamisch alle .dl-bestanden in de projectmap
    mapfile -t programs < <(find "$project_dir" -maxdepth 1 -name "*.dl" | sort)
    if [ ${#programs[@]} -eq 0 ]; then
        echo "🤷 Geen .dl-bestanden gevonden in '$project_dir', wordt overgeslagen."
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
        echo "📦 Verwerken van dataset: $dataset_name"
        echo "------------------------------------------------------------"

        # Stap 1: Genereer de data voor deze specifieke run
        echo "  -> Genereren van data..."
        python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir_for_run"

        # Stap 2: Loop over elk gevonden programma
        for program_path in "${programs[@]}"; do
            program_name=$(basename "$program_path" .dl)
            
            output_run_dir="${output_base_dir}/${program_name}/${dataset_name}"
            benchmark_run_dir="${benchmarks_base_dir}/${program_name}/${dataset_name}"
            profile_file="${benchmark_run_dir}/profile_report.html"

            echo "  -> 🔥 Benchmarken van '$program_name'..."
            
            # Maak de outputmappen aan
            mkdir -p "$output_run_dir"
            mkdir -p "$benchmark_run_dir"
            
            # Stap 3: Voer Soufflé uit met timeout en profiling
            if timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir_for_run" -D "$output_run_dir" -p "$profile_file" "$program_path"; then
                echo "     ✅ Voltooid."
            else
                exit_status=$?
                if [ $exit_status -eq 124 ]; then
                    echo "     ⚠️ TIMEOUT: Uitvoering duurde langer dan $TIMEOUT_SECONDS seconden en is gestopt."
                else
                    echo "     ❌ FOUT: Soufflé eindigde met een fout (exit code: $exit_status)."
                fi
            fi
        done
    done
done

echo ""
echo "🎉 Alle benchmarks zijn voltooid!"