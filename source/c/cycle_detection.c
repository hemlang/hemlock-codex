// gcc -o cycle_detection cycle_detection.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int node, idx; } Frame;

int has_cycle(int adj[][4], int adj_count[], int n) {
    int *color = calloc(n, sizeof(int)); // 0=white, 1=gray, 2=black
    Frame *stack = malloc(n * sizeof(Frame));
    int result = 0;

    for (int start = 0; start < n && !result; start++) {
        if (color[start] != 0) continue;
        int top = 0;
        stack[top++] = (Frame){start, 0};
        color[start] = 1;

        while (top > 0 && !result) {
            Frame *f = &stack[top - 1];
            int u = f->node;
            if (f->idx < adj_count[u]) {
                int v = adj[u][f->idx];
                f->idx++;
                if (color[v] == 1) { result = 1; break; }
                if (color[v] == 0) {
                    color[v] = 1;
                    stack[top++] = (Frame){v, 0};
                }
            } else {
                color[u] = 2;
                top--;
            }
        }
    }
    free(color);
    free(stack);
    return result;
}

int main(void) {
    // Graph 1: has cycle (0->1->2->0)
    int adj1[4][4] = {{1},{2},{0,3},{-1}};
    int cnt1[] = {1,1,2,0};
    if (has_cycle(adj1, cnt1, 4)) printf("graph1: cycle detected\n");
    else printf("graph1: no cycle\n");

    // Graph 2: no cycle (DAG)
    int adj2[4][4] = {{1,2},{3},{3},{-1}};
    int cnt2[] = {2,1,1,0};
    if (has_cycle(adj2, cnt2, 4)) printf("graph2: cycle detected\n");
    else printf("graph2: no cycle\n");

    return 0;
}
