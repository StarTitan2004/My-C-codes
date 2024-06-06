#include <stdio.h>
#include <stdlib.h>

#define N 64

int parent[N];
int sz[N];

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;    
}

int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void union_set(int a , int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b]) {
            int temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
	int i;
	int j;
	int k;
    for (i = 0; i < N; i++) {
        make_set(i);
    }
    
    int n = 6;
    int m = 8;
    
    int edges[4][3] = {{1, 1, 2}, {2, 3, 2}, {1, 3, 2}, {1, 32, 2}};
    for (i = 0; i < m - 1; i++) {
        for (j = 0; j < m - i - 1; j++) {
            if (edges[j][0] > edges[j + 1][0]) {
                int temp[3];
                for (k = 0; k < 3; k++) {
                    temp[k] = edges[j][k];
                    edges[j][k] = edges[j + 1][k];
                    edges[j + 1][k] = temp[k];
                }
            }
        }
    }

    int cost = 0;
    for (i = 0; i < m; i++) {
        int w = edges[i][0];
        int u = edges[i][1];
        int v = edges[i][2];
        int x = find_set(u);
        int y = find_set(v);
        if (x == y) {
            continue;
        } else {
            printf("%d %d\n", u, v);
            cost += w;
            union_set(u, v);
        }
    }
    printf("Total Cost: %d\n", cost);
    return 0;
}

