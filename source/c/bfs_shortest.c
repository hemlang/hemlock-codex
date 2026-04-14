// gcc -o bfs_shortest bfs_shortest.c
#include <stdio.h>

// Graph: 0->[1,2], 1->[3], 2->[3,4], 3->[5], 4->[5]
#define N 6

int adj[N][2] = {{1,2},{3,-1},{3,4},{5,-1},{5,-1},{-1,-1}};
int adj_count[] = {2, 1, 2, 1, 1, 0};

int main(void) {
    int visited[N] = {0}, dist[N], prev[N];
    for (int i = 0; i < N; i++) { dist[i] = -1; prev[i] = -1; }

    int queue[N];
    int head = 0, tail = 0;
    queue[tail++] = 0;
    visited[0] = 1;
    dist[0] = 0;

    while (head < tail) {
        int u = queue[head++];
        if (u == 5) break;
        for (int e = 0; e < adj_count[u]; e++) {
            int v = adj[u][e];
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                prev[v] = u;
                queue[tail++] = v;
            }
        }
    }

    // Reconstruct path
    int path[N], plen = 0;
    for (int c = 5; c >= 0; c = prev[c]) {
        path[plen++] = c;
        if (prev[c] < 0) break;
    }

    printf("distance: %d\n", dist[5]);
    printf("path:");
    for (int i = plen - 1; i >= 0; i--) printf(" %d", path[i]);
    printf("\n");
    return 0;
}
