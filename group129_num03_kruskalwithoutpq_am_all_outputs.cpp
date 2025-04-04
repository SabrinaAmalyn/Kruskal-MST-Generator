#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Edge {
    int sourceVertex, destinationVertex, weight;
};

struct Subset {
    int parent, rank;
};

int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(vector<Subset>& subsets, int elementA, int elementB) {
    int rootA = find(subsets, elementA);
    int rootB = find(subsets, elementB);

    if (subsets[rootA].rank < subsets[rootB].rank)
        subsets[rootA].parent = rootB;
    else if (subsets[rootA].rank > subsets[rootB].rank)
        subsets[rootB].parent = rootA;
    else {
        subsets[rootB].parent = rootA;
        subsets[rootA].rank++;
    }
}

bool compareEdges(const Edge& edgeA, const Edge& edgeB) {
    return edgeA.weight < edgeB.weight;
}

vector<Edge> kruskalMST(vector<Edge>& edges, int numVertices) {
    vector<Edge> result;
    vector<Subset> subsets(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    sort(edges.begin(), edges.end(), compareEdges);

    int edgeCount = 0;
    int index = 0;
    while (edgeCount < numVertices - 1 && index < edges.size()) {
        Edge nextEdge = edges[index++];
        int x = find(subsets, nextEdge.sourceVertex);
        int y = find(subsets, nextEdge.destinationVertex);

        if (x != y) {
            result.push_back(nextEdge);
            Union(subsets, x, y);
            edgeCount++;
        }
    }

    return result;
}

int main() {

    vector<string> inputFiles = {
        "kruskalwithoutpq_kruskalwithpq_am_00000010_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00000100_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00001000_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00010000_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00015000_input.txt"
    };

    vector<string> outputFiles = {
        "kruskalwithoutpq_am_00000010_output.txt",
        "kruskalwithoutpq_am_00000100_output.txt",
        "kruskalwithoutpq_am_00001000_output.txt",
        "kruskalwithoutpq_am_00010000_output.txt",
        "kruskalwithoutpq_am_00015000_output.txt"
    };

    for (int i = 0; i < inputFiles.size(); ++i) {
        string inputFile = inputFiles[i];
        string outputFile = outputFiles[i];

        ifstream input(inputFile);
        ofstream output(outputFile);

        int numVertices;
        input >> numVertices;

        vector<int> vertexIndexes(numVertices);
        vector<string> vertexNames(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            input >> vertexIndexes[i] >> vertexNames[i];
        }

        vector<Edge> edges;
        string weight;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                input >> weight;
                if (weight != "i") {
                    int w = stoi(weight);
                    edges.push_back({ i, j, w });
                }
            }
        }

        auto start = chrono::high_resolution_clock::now();
        vector<Edge> mst = kruskalMST(edges, numVertices);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        output << numVertices << endl;
        for (int i = 0; i < numVertices; ++i) {
            output << vertexIndexes[i] << " " << vertexNames[i] << endl;
        }

        int totalWeight = 0;
        for (const Edge& edge : mst) {
            output << vertexNames[edge.sourceVertex] << " " << vertexNames[edge.destinationVertex] << " " << edge.weight << endl;
            totalWeight += edge.weight;
        }

        output << totalWeight << endl;
        output << duration.count() << "s" << endl;

        input.close();
        output.close();
    }

    return 0;
}
