// gcc -o lis lis.c
#include <stdio.h>

int main(void) {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = 8;
    int dp[8];
    for (int i = 0; i < n; i++) dp[i] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; i++) if (dp[i] > max_len) max_len = dp[i];

    printf("lis length: %d\n", max_len);
    return 0;
}
