def fibonacci(n):
    memo = {0: 0, 1: 1}
    for i in range(2, n + 1):
        memo[i] = memo[i - 1] + memo[i - 2]
    return memo[n]

n = 40
result = fibonacci(n)
print(f"fib({n}): {result}")
