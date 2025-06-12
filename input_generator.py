import random
import os

# NUM_NODES = 10       
# MAX_EDGES = NUM_NODES * (NUM_NODES - 1)
# NUM_EDGES = min(100, MAX_EDGES)

# edges = set()

# while len(edges) < NUM_EDGES:
#     a = random.randint(1, NUM_NODES)
#     b = random.randint(1, NUM_NODES)
#     if a != b:
#         edges.add((a, b))

# os.makedirs("facts", exist_ok=True)

# with open("facts/edge.facts", "w") as f:
#     for a, b in edges:
#         f.write(f"{a}\t{b}\n")


NUM_NODES = 100
MAX_EDGES = NUM_NODES * (NUM_NODES - 1)
NUM_EDGES = min(2000, MAX_EDGES)

edges = set()

while len(edges) < NUM_EDGES:
    a = random.randint(1, NUM_NODES)
    b = random.randint(1, NUM_NODES)
    if a != b:
        edges.add((a, b))

os.makedirs("facts", exist_ok=True)

with open("facts/edge.facts", "w") as f:
    for a, b in edges:
        f.write(f"{a}\t{b}\n")

# NUM_NODES = 1000
# MAX_EDGES = NUM_NODES * (NUM_NODES - 1)
# NUM_EDGES = min(100000, MAX_EDGES)

# edges = set()

# while len(edges) < NUM_EDGES:
#     a = random.randint(1, NUM_NODES)
#     b = random.randint(1, NUM_NODES)
#     if a != b:
#         edges.add((a, b))

# os.makedirs("facts", exist_ok=True)

# with open("facts/edge.facts", "w") as f:
#     for a, b in edges:
#         f.write(f"{a}\t{b}\n")

# NUM_NODES = 10000
# MAX_EDGES = NUM_NODES * (NUM_NODES - 1)
# NUM_EDGES = min(1000000, MAX_EDGES)

# edges = set()

# while len(edges) < NUM_EDGES:
#     a = random.randint(1, NUM_NODES)
#     b = random.randint(1, NUM_NODES)
#     if a != b:
#         edges.add((a, b))

# os.makedirs("facts", exist_ok=True)

# with open("facts/edge.facts", "w") as f:
#     for a, b in edges:
#         f.write(f"{a}\t{b}\n")


# import random
# import os

# NUM_NODES = 100       # ≪ veel kleiner dan 1000
# MAX_EDGES = NUM_NODES * (NUM_NODES - 1)
# NUM_EDGES = min(2000, MAX_EDGES)  # 2000 edges is beheersbaar

# edges = set()

# while len(edges) < NUM_EDGES:
#     a = random.randint(1, NUM_NODES)
#     b = random.randint(1, NUM_NODES)
#     if a != b:
#         edges.add((a, b))

# os.makedirs("facts", exist_ok=True)

# with open("facts/edge.facts", "w") as f:
#     for a, b in edges:
#         f.write(f"{a}\t{b}\n")
