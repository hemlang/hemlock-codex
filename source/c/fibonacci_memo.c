// gcc -o fibonacci_memo fibonacci_memo.c
#include <stdio.h>

int main(void) {
    int n = 40;
    long long memo[41];
    memo[0] = 0; memo[1] = 1;
    for (int i = 2; i <= n; i++) memo[i] = memo[i-1] + memo[i-2];
    printf("fib(%d): %lld\n", n, memo[n]);
    return 0;
}
