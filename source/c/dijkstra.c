// gcc -o dijkstra dijkstra.c
// Graph: A->B(4), A->C(2), B->D(3), C->B(1), C->D(5), D->E(1)
// Nodes: A=0, B=1, C=2, D=3, E=4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define INF 999999999

typedef struct { int to, weight; } Edge;

Edge adj[N][3];
int adj_count[N];

void add_edge(int from, int to, int weight) {
    int c = adj_count[from];
    adj[from][c].to = to;
    adj[from][c].weight = weight;
    adj_count[from]++;
}

int main(void) {
    memset(adj_count, 0, sizeof(adj_count));
    add_edge(0, 1, 4); add_edge(0, 2, 2);
    add_edge(1, 3, 3);
    add_edge(2, 1, 1); add_edge(2, 3, 5);
    add_edge(3, 4, 1);

    int dist[N], prev[N];
    int visited[N];
    for (int i = 0; i < N; i++) { dist[i] = INF; prev[i] = -1; visited[i] = 0; }
    dist[0] = 0;

    for (int i = 0; i < N; i++) {
        int u = -1, min_d = INF;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < min_d) { min_d = dist[j]; u = j; }
        }
        if (u < 0 || u == 4) break;
        visited[u] = 1;
        for (int e = 0; e < adj_count[u]; e++) {
            int v = adj[u][e].to;
            int alt = dist[u] + adj[u][e].weight;
            if (alt < dist[v]) { dist[v] = alt; prev[v] = u; }
        }
    }

    // Reconstruct path from E(4) to A(0)
    char *names[] = {"A", "B", "C", "D", "E"};
    int path[N], plen = 0;
    for (int c = 4; c >= 0; c = prev[c]) {
        path[plen++] = c;
        if (prev[c] < 0) break;
    }
    printf("shortest A->E: %d\n", dist[4]);
    printf("path:");
    for (int i = plen - 1; i >= 0; i--) printf(" %s", names[path[i]]);
    printf("\n");
    return 0;
}
