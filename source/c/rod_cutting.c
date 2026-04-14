// gcc -o rod_cutting rod_cutting.c
#include <stdio.h>

int main(void) {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    int np = 9;
    int n = 8;

    int dp[9];
    for (int i = 0; i <= n; i++) dp[i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j < np) {
                int candidate = prices[j] + dp[i - j];
                if (candidate > dp[i]) dp[i] = candidate;
            }
        }
    }

    printf("max revenue: %d\n", dp[n]);
    return 0;
}
