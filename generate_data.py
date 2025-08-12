import random
from pathlib import Path
import argparse

def generate_graph_data(num_nodes: int, density: float) -> set[tuple[int, int]]:
    """Genereert een willekeurige set van 'edges' voor een graaf."""
    edges = set()
    nodes = list(range(num_nodes))
    for u in nodes:
        for v in nodes:
            if u == v:
                continue
            if random.random() < density:
                edges.add((u, v))
    return edges

def write_facts_to_file(directory: Path, filename: str, data: set[tuple[int, int]]):
    """Schrijft een set van tuples naar een tab-gescheiden .facts bestand."""
    with open(directory / filename, "w") as f:
        # Sorteren voor consistente, reproduceerbare output
        for item in sorted(list(data)):
            f.write(f"{item[0]}\t{item[1]}\n")

def main():
    """Hoofdfunctie voor het genereren van datasets."""
    parser = argparse.ArgumentParser(description="Genereer testdata voor Soufflé-programma's.")
    parser.add_argument("--nodes", type=int, required=True, help="Aantal knopen in de graaf.")
    parser.add_argument("--density", type=float, required=True, help="De kans (0.0-1.0) dat een edge bestaat.")
    parser.add_argument("--type", type=str, required=True, choices=['edge', 'rs', 'blue_red'], help="Type data: 'edge', 'rs' of 'blue_red'.")
    parser.add_argument("--output_dir", type=str, required=True, help="Exacte map om de .facts bestanden op te slaan.")
    
    args = parser.parse_args()
    
    output_path = Path(args.output_dir)
    # De map wordt nu aangemaakt door het bash-script, maar een check kan geen kwaad.
    output_path.mkdir(parents=True, exist_ok=True)
    
    if args.type == 'edge':
        edges = generate_graph_data(args.nodes, args.density)
        write_facts_to_file(output_path, "edge.facts", edges)
        
    elif args.type == 'rs':
        r_facts = generate_graph_data(args.nodes, args.density)
        s_facts = generate_graph_data(args.nodes, args.density)
        write_facts_to_file(output_path, "R.facts", r_facts)
        write_facts_to_file(output_path, "S.facts", s_facts)

    elif args.type == 'blue_red':
        blue_edges = generate_graph_data(args.nodes, args.density)
        red_edges = generate_graph_data(args.nodes, args.density)
        write_facts_to_file(output_path, "Blue.facts", blue_edges)
        write_facts_to_file(output_path, "Red.facts", red_edges)

    print(f"Data gegenereerd in '{output_path}'")

if __name__ == "__main__":
    main()