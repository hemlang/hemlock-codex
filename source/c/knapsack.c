// gcc -o knapsack knapsack.c
#include <stdio.h>

int main(void) {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int capacity = 8;
    int n = 4;

    int dp[5][9];
    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= capacity; w++)
            dp[i][w] = 0;

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i-1][w];
            if (weights[i-1] <= w) {
                int with_item = dp[i-1][w - weights[i-1]] + values[i-1];
                if (with_item > dp[i][w]) dp[i][w] = with_item;
            }
        }
    }

    printf("max value: %d\n", dp[n][capacity]);
    return 0;
}
