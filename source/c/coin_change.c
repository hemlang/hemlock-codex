// gcc -o coin_change coin_change.c
#include <stdio.h>

int main(void) {
    int coins[] = {1, 5, 10, 25};
    int nc = 4;
    int amount = 36;

    int dp[37];
    for (int i = 0; i <= amount; i++) dp[i] = amount + 1;
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < nc; j++) {
            if (coins[j] <= i) {
                int candidate = dp[i - coins[j]] + 1;
                if (candidate < dp[i]) dp[i] = candidate;
            }
        }
    }

    int result = dp[amount] > amount ? -1 : dp[amount];
    printf("min coins: %d\n", result);
    return 0;
}
