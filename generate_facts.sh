#!/bin/bash

# Projecten en datasets waarvoor facts moeten worden aangemaakt
PROJECT_DIRS=(
    "Example_1:edge"
    # "Example_2:rs"
    #"Positive_To_Negative_Example_1:blue_red"
)
DATASETS=(
    # "500 0.02"  # Ijle graaf
     #"5000 0.1"   # Matige dichtheid
	"500 0.1"   # Matige dichtheid

    # "500 0.5"   # Dicht
    # "500 1.0"   # Volledig
)

echo "Start of generating facts..."

for project_config in "${PROJECT_DIRS[@]}"; do
    IFS=':' read -r project_dir data_type <<< "$project_config"

    echo ""
    echo "Projectdir: $project_dir"

    facts_base_dir="$project_dir/facts"
    mkdir -p "$facts_base_dir"

    for dataset_config in "${DATASETS[@]}"; do
        read -r nodes density <<< "$dataset_config"
        dataset_name="data_${nodes}nodes_${density//./p}density"
        facts_dir="${facts_base_dir}/${dataset_name}"

        echo "🔹 Dataset: $dataset_name"

        if [ ! -d "$facts_dir" ]; then
            echo "Generating facts"
            python3 generate_data.py --nodes "$nodes" --density "$density" --type "$data_type" --output_dir "$facts_dir"
        else
            echo "Facts already exist => Skip..."
        fi
    done
done

echo ""
echo "Facts made! Done!"
