#include <stdio.h>
#include <stdbool.h>
#define MAX_NODES 6

void bfs(int graph[MAX_NODES][MAX_NODES], int numNodes, int startNode) {
    bool visited[MAX_NODES];
    int i;
    for (i = 0; i < numNodes; ++i)
        visited[i] = false;

    int queue[MAX_NODES], front = -1, rear = -1;
    visited[startNode] = true;
    queue[++rear] = startNode;

    while (front != rear) {
        int currentNode = queue[++front];
        printf("%d ", currentNode);
        for (i = 0; i < numNodes; ++i) {
            if (graph[currentNode][i] && !visited[i]) {
                visited[i] = true;
                queue[++rear] = i;
            }
        }
    }
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0}
    };

    printf("BFS traversal starting from node 0: ");
    bfs(graph, MAX_NODES, 0);

    return 0;
}

