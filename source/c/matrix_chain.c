// gcc -o matrix_chain matrix_chain.c
#include <stdio.h>

#define INF 999999999
#define MAXN 10

int dp[MAXN][MAXN];

int main(void) {
    int dims[] = {10, 30, 5, 60};
    int nd = 4;
    int n = nd - 1; // number of matrices

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            dp[i][j] = INF;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }

    printf("min multiplications: %d\n", dp[0][n-1]);
    return 0;
}
