import random

# Target sizes
sizes = [10, 100, 1000, 10000, 15000]

def generate_input_file(num_vertices):
    filename = f"kruskalwithoutpq_kruskalwithpq_am_{num_vertices:08}_input.txt"
    with open(filename, "w") as f:
        f.write(f"{num_vertices}\n")
        
        # Write vertex index and names
        for i in range(num_vertices):
            f.write(f"{i} V{i}\n")
        
        # Generate adjacency matrix
        for i in range(num_vertices):
            row = []
            for j in range(num_vertices):
                if i == j:
                    row.append("0")  # No self-loop
                elif random.random() < 0.1:  # 10% chance of edge
                    weight = random.randint(1, 20)
                    row.append(str(weight))
                else:
                    row.append("i")  # No connection
            f.write(" ".join(row) + "\n")
    print(f"Generated: {filename}")

# Generate all files
for size in sizes:
    generate_input_file(size)
