#!/usr/bin/env bash

# Maak een map voor de output, als deze nog niet bestaat.
# De '-p' optie zorgt ervoor dat er geen foutmelding komt als de map al bestaat.
mkdir -p rapporten

# 0: Origineel programma
echo "Verwerken: 0_origineel_programma_bounded_negation_voor_herschrijving.dl"
IN_FILE="0_origineel_programma_bounded_negation_voor_herschrijving.dl"
OUT_PREFIX="rapporten/0_semi"
souffle "$IN_FILE" --show=transformed-ram      > "${OUT_PREFIX}.ram.txt"
souffle "$IN_FILE" --show=precedence-graph    > "${OUT_PREFIX}.precedencegraph.txt"
souffle "$IN_FILE" --show=scc-graph           > "${OUT_PREFIX}.sccgraph.txt"
echo

# 2: Propositie 3.9
echo "Verwerken: 2_proposition_3.9_toegepast.dl"
IN_FILE="2_proposition_3.9_toegepast.dl"
OUT_PREFIX="rapporten/2_prop_3_9"
souffle "$IN_FILE" --show=transformed-ram      > "${OUT_PREFIX}.ram.txt"
souffle "$IN_FILE" --show=precedence-graph    > "${OUT_PREFIX}.precedencegraph.txt"
souffle "$IN_FILE" --show=scc-graph           > "${OUT_PREFIX}.sccgraph.txt"
echo

# 3: Unfolding
echo "Verwerken: 3_unfolding.dl"
IN_FILE="3_unfolding.dl"
OUT_PREFIX="rapporten/3_unfolding"
souffle "$IN_FILE" --show=transformed-ram      > "${OUT_PREFIX}.ram.txt"
souffle "$IN_FILE" --show=precedence-graph    > "${OUT_PREFIX}.precedencegraph.txt"
souffle "$IN_FILE" --show=scc-graph           > "${OUT_PREFIX}.sccgraph.txt"
echo

# 6. Laatste optimalisaties
echo "Verwerken: 6_laatste_optimalisaties.dl"
IN_FILE="6_laatste_optimalisaties.dl"
OUT_PREFIX="rapporten/6_pos"
souffle "$IN_FILE" --show=transformed-ram      > "${OUT_PREFIX}.ram.txt"
souffle "$IN_FILE" --show=precedence-graph    > "${OUT_PREFIX}.precedencegraph.txt"
souffle "$IN_FILE" --show=scc-graph           > "${OUT_PREFIX}.sccgraph.txt"
echo

echo "Done! Reports generated!"