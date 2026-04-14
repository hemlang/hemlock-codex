// gcc -o floyd_warshall floyd_warshall.c
#include <stdio.h>

#define N 4
#define INF 999999999

int main(void) {
    int dist[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = (i == j) ? 0 : INF;

    dist[0][1] = 3; dist[0][3] = 7;
    dist[1][0] = 8; dist[1][2] = 2;
    dist[2][0] = 5; dist[2][3] = 1;
    dist[3][0] = 2;

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("distance matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j > 0) printf(" ");
            if (dist[i][j] >= INF) printf("INF");
            else printf("%d", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}
