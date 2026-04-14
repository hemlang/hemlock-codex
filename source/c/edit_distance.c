// gcc -o edit_distance edit_distance.c
#include <stdio.h>
#include <string.h>

#define MAXN 100

int dp[MAXN+1][MAXN+1];
int min3(int a, int b, int c) { return a < b ? (a < c ? a : c) : (b < c ? b : c); }

int main(void) {
    const char *a = "kitten";
    const char *b = "sitting";
    int m = strlen(a), n = strlen(b);

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min3(dp[i][j-1]+1, dp[i-1][j]+1, dp[i-1][j-1]+1);
        }
    }

    printf("edit distance: %d\n", dp[m][n]);
    return 0;
}
