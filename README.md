Kruskal Minimum Spanning Tree Generator
--

This C++ program uses Kruskal's Algorithm to find the Minimum Spanning Tree (MST) of a graph. It reads graphs from input files (in adjacency matrix format), builds the MST, and writes the results to output files. The program also measures and logs the time taken to compute the MST.

Features
-
1. Efficient MST generation using Kruskal’s Algorithm

2. Union-Find (Disjoint Set) with optimizations

3. Supports multiple graph sizes

4. Measures execution time

How to Use
-
1. Prepare input files with vertex info and adjacency matrix using the "generate_kruskal_inputs.py" script.
![image](https://github.com/user-attachments/assets/9861d88d-8f4a-406b-b9dd-028d57b8a690)
2. Compile the code in "group129_num03_kruskalwithoutpq_am_all_outputs.cpp".
3. Output files will show:
- List of MST edges
- Total weight of the MST
- Time taken to compute
