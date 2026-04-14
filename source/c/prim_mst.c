// gcc -o prim_mst prim_mst.c
#include <stdio.h>

#define N 5
#define INF 999999999

int adj[N][N] = {
    {0,2,0,6,0},
    {2,0,3,8,5},
    {0,3,0,0,7},
    {6,8,0,0,9},
    {0,5,7,9,0}
};

int main(void) {
    int in_mst[N] = {0}, key[N], parent[N];
    for (int i = 0; i < N; i++) { key[i] = INF; parent[i] = -1; }
    key[0] = 0;

    for (int count = 0; count < N; count++) {
        int u = -1, min_key = INF;
        for (int i = 0; i < N; i++) {
            if (!in_mst[i] && key[i] < min_key) { min_key = key[i]; u = i; }
        }
        in_mst[u] = 1;
        for (int v = 0; v < N; v++) {
            if (adj[u][v] > 0 && !in_mst[v] && adj[u][v] < key[v]) {
                key[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;
    printf("prim MST edges:\n");
    for (int i = 1; i < N; i++) {
        printf("  %d - %d (weight %d)\n", parent[i], i, adj[parent[i]][i]);
        total += adj[parent[i]][i];
    }
    printf("total weight: %d\n", total);
    return 0;
}
