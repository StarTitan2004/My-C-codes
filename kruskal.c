#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Function prototypes
struct Graph* createGraph(int V, int E);
void printMST(struct Edge* MST, int n);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void KruskalMST(struct Graph* graph);

int main() {
    // Example graph
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    struct Graph* graph = createGraph(V, E);

    // Add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // Add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // Add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // Add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // Add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Utility function to print the MST
void printMST(struct Edge* MST, int n) {
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d -- %d\tWeight: %d\n", MST[i].src, MST[i].dest, MST[i].weight);
    }
}

// Find set of an element i (uses path compression technique)
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets x and y (uses union by rank)
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator function for qsort
int compareEdges(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal's algorithm to find MST
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge MST[V - 1]; // Array to store the MST
    int e = 0; // Index variable for MST
    int i = 0; // Index variable for sorted edges array

    // Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));

    // Initialize subsets for each element
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Iterate through all sorted edges
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause cycle, include it in MST
        if (x != y) {
            MST[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printMST(MST, V - 1);

    // Free memory
    free(subsets);
}
