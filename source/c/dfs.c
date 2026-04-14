// gcc -o dfs dfs.c
#include <stdio.h>

// Graph: 0->[1,2], 1->[3,4], 2->[5], 3->[], 4->[5], 5->[]
#define N 6

int adj[N][2] = {{1,2},{3,4},{5,-1},{-1,-1},{5,-1},{-1,-1}};
int adj_count[] = {2, 2, 1, 0, 1, 0};

int main(void) {
    int visited[N] = {0};
    int order[N];
    int order_len = 0;

    int stack[N * 2];
    int top = 0;
    stack[top++] = 0;

    while (top > 0) {
        int u = stack[--top];
        if (visited[u]) continue;
        visited[u] = 1;
        order[order_len++] = u;
        // Push neighbors in reverse so leftmost visited first
        for (int i = adj_count[u] - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!visited[v]) stack[top++] = v;
        }
    }

    printf("dfs:");
    for (int i = 0; i < order_len; i++) printf(" %d", order[i]);
    printf("\n");
    return 0;
}
