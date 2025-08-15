#!/bin/bash

# Configuratie, welke programma runnen met welke data
PROJECT_DIRS=(
    # "Example_1:edge"
    # "Example_2:rs"
    "Positive_To_Negative_Example_1:blue_red"
)
DATASETS=(
    #"500 0.02"  # Ijle graaf
     "500 0.1"   # Matige dichtheid
    # "500 0.5"   # Dicht
    # "500 1.0"   # Volledig
)
TIMEOUT_SECONDS=100 # programma stop wanneer benchmark te lang duurt
WARMUP_RUNS=5
BENCHMARK_RUNS=10


# Ctrl + C moet ervoor zorgen dat de benchmarks worden afgebroken
cleanup() {
    echo ""
    echo "Benchmark onderbroken. Processen worden opgeruimd..."
    pkill -TERM souffle 2>/dev/null
    sleep 2
    pkill -KILL souffle 2>/dev/null
    echo "Benchmarkrun afgebroken"
    exit 1
}
trap cleanup SIGINT SIGTERM # Ervoor zorgen dat Cleanup gebeurt wanneer gebruiker benchmark onderbreekt (ctrl+C of ctrl +Z)

echo "Tududuuuuu!!!!! Starten van de benchmarks..."

for project_config in "${PROJECT_DIRS[@]}"; do
    IFS=':' read -r project_dir data_type <<< "$project_config"

    echo ""
    echo "Projectmap: $project_dir"

    mapfile -t programs < <(find "$project_dir" -maxdepth 1 -name "*.dl" | sort) # Zoek de Datalogprogramma's gesorteerd op naam (naam van programma begint steeds met cijfer wat wijst op welke versie van het programma het is)
    if [ ${#programs[@]} -eq 0 ]; then
        echo "Geen Datalog-bestanden gevonden in $project_dir" # Map is leeg => we gaan naar de volgende map
        continue
    fi

    facts_base_dir="$project_dir/facts" # Facts zitten in submap facts
    output_base_dir="$project_dir/output" # Resultaten worden weggeschreven naar submap output
    benchmark_dir="${project_dir}/benchmarks" # Benchmarks worden weggeschreven naar submap benchmarks
    mkdir -p "$benchmark_dir" # Wanneeer benchmark map nog niet bestaat wordt deze aangemaakt.

    # Warmupfase
    if [ "$WARMUP_RUNS" -gt 0 ]; then #Wanneer er warmup runs zijn
        echo "Uitvoeren van $WARMUP_RUNS warmup-runs..."

        middle_index=$(( (${#DATASETS[@]} - 1) / 2 )) # We runnen een warmup run op de middelste dataset uit de lijst van datasets
        warmup_dataset_config=${DATASETS[$middle_index]}
        read -r w_nodes w_density <<< "$warmup_dataset_config" # Lees de node density die we willen voor deze run
        warmup_dataset="data_${w_nodes}nodes_${w_density//./p}density" # Zet de density vast voor deze run
        facts_dir="${facts_base_dir}/${warmup_dataset}"

        if [ ! -d "$facts_dir" ]; then
            echo "Genereren van warmup-facts..."
            python3 generate_data.py --nodes "$w_nodes" --density "$w_density" --type "$data_type" --output_dir "$facts_dir" # Roep python script op om facts te maken voor warmup run
        else
            echo "Warmup-facts gevonden." # Er waren reeds facts beschikbaar
        fi

        warmup_program_path="${project_dir}/0_origineel_programma_bounded_negation_voor_herschrijving.dl"
        warmup_program_name=$(basename "$warmup_program_path" .dl)
        output_dir="${output_base_dir}/warmup_${warmup_program_name}/${warmup_dataset}"
        mkdir -p "$output_dir"

        for i in $(seq 1 $WARMUP_RUNS); do
            log_file="${benchmark_dir}/warmup_${warmup_program_name}_${warmup_dataset}_${i}.json"
            run_output="${output_dir}/run_${i}"
            mkdir -p "$run_output"
            
            echo -n "Warmup run $i... "
            (
                ulimit -v 5485760 #10485760 # Zet de memory limit voor dit process zodat het niet in error gaat https://phoenixnap.com/kb/ulimit-linux-command
                timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir" -D "$run_output" -p "$log_file" "$warmup_program_path"
            )& wait $!


            if [ $? -eq 0 ]; then
                echo "OK"
            else
                echo "Fout of timeout opgetreden"
            fi
        done
        echo "Joepieee!!! Warmup voltooid."
    fi

    # Benchmark runs
    for dataset_config in "${DATASETS[@]}"; do
        read -r nodes density <<< "$dataset_config"
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir="${facts_base_dir}/${dataset_name}"

        echo "🔹 Dataset: $dataset_name"

        if [ ! -d "$facts_dir" ]; then
            echo "Genereren van facts..."
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir"
        else
            echo "Facts gevonden."
        fi

        for program_path in "${programs[@]}"; do
            program_name=$(basename "$program_path" .dl)
            output_dir="${output_base_dir}/${program_name}/${dataset_name}"
            mkdir -p "$output_dir"

            echo "Programma: $program_name"

            for i in $(seq 1 $BENCHMARK_RUNS); do
                log_file="${benchmark_dir}/${program_name}_${dataset_name}_run${i}.json"
                run_output="${output_dir}/run_${i}"
                mkdir -p "$run_output"

                echo -n "Benchmark $i... "
                (
                    ulimit -v 5485760 # https://phoenixnap.com/kb/ulimit-linux-command
                    timeout "$TIMEOUT_SECONDS" souffle -F "$facts_dir" -D "$run_output" -p "$log_file" "$program_path"
                ) & wait $!

                if [ $? -eq 0 ]; then
                    echo "OK"
                else
                    echo "Fout of timeout"
                fi
            done
        done
    done
done

echo ""
echo "Alle benchmarks zijn afgerond! Resultaten staan in 'benchmarks/' binnen elke projectmap."
