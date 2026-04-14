// gcc -o kruskal_mst kruskal_mst.c
#include <stdio.h>

#define N 5

int uf_parent[N], uf_rank[N];

void uf_init(void) {
    for (int i = 0; i < N; i++) { uf_parent[i] = i; uf_rank[i] = 0; }
}

int uf_find(int x) {
    while (uf_parent[x] != x) {
        uf_parent[x] = uf_parent[uf_parent[x]];
        x = uf_parent[x];
    }
    return x;
}

int uf_union(int a, int b) {
    int ra = uf_find(a), rb = uf_find(b);
    if (ra == rb) return 0;
    if (uf_rank[ra] < uf_rank[rb]) uf_parent[ra] = rb;
    else if (uf_rank[ra] > uf_rank[rb]) uf_parent[rb] = ra;
    else { uf_parent[rb] = ra; uf_rank[ra]++; }
    return 1;
}

typedef struct { int u, v, w; } Edge;

int main(void) {
    Edge edges[] = {{0,1,2},{0,3,6},{1,2,3},{1,3,8},{1,4,5},{2,4,7},{3,4,9}};
    int ne = 7;

    // Insertion sort by weight
    for (int i = 1; i < ne; i++) {
        Edge ke = edges[i]; int j = i - 1;
        while (j >= 0 && edges[j].w > ke.w) { edges[j+1] = edges[j]; j--; }
        edges[j+1] = ke;
    }

    uf_init();

    Edge mst[N-1];
    int mst_len = 0, total = 0;
    for (int i = 0; i < ne && mst_len < N - 1; i++) {
        if (uf_union(edges[i].u, edges[i].v)) {
            mst[mst_len++] = edges[i];
            total += edges[i].w;
        }
    }

    printf("kruskal MST edges:\n");
    for (int i = 0; i < mst_len; i++) {
        printf("  %d - %d (weight %d)\n", mst[i].u, mst[i].v, mst[i].w);
    }
    printf("total weight: %d\n", total);
    return 0;
}
