// gcc -o topological_sort topological_sort.c
#include <stdio.h>

// DAG: 5->[0,2], 4->[0,1], 2->[3], 3->[1]
#define N 6

int adj[N][2] = {{-1,-1},{-1,-1},{3,-1},{1,-1},{0,1},{0,2}};
int adj_count[] = {0, 0, 1, 1, 2, 2};

int main(void) {
    int in_degree[N] = {0};
    for (int u = 0; u < N; u++) {
        for (int e = 0; e < adj_count[u]; e++) {
            in_degree[adj[u][e]]++;
        }
    }

    int queue[N];
    int head = 0, tail = 0;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) queue[tail++] = i;
    }

    int order[N], order_len = 0;
    while (head < tail) {
        int u = queue[head++];
        order[order_len++] = u;
        for (int e = 0; e < adj_count[u]; e++) {
            int v = adj[u][e];
            in_degree[v]--;
            if (in_degree[v] == 0) queue[tail++] = v;
        }
    }

    printf("topological order:");
    for (int i = 0; i < order_len; i++) printf(" %d", order[i]);
    printf("\n");
    return 0;
}
