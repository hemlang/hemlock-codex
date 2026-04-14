// gcc -o lcs lcs.c
#include <stdio.h>
#include <string.h>

#define MAXN 100

int dp[MAXN+1][MAXN+1];

int main(void) {
    const char *a = "ABCBDAB";
    const char *b = "BDCAB";
    int m = strlen(a), n = strlen(b);

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
        }
    }

    // Backtrack
    char result[MAXN+1];
    int ri = 0, i = m, j = n;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { result[ri++] = a[i-1]; i--; j--; }
        else if (dp[i-1][j] >= dp[i][j-1]) i--;
        else j--;
    }
    // Reverse
    for (int l = 0, r = ri - 1; l < r; l++, r--) {
        char tmp = result[l]; result[l] = result[r]; result[r] = tmp;
    }
    result[ri] = '\0';

    printf("lcs length: %d\n", dp[m][n]);
    printf("lcs: %s\n", result);
    return 0;
}
