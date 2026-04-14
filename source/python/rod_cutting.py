def rod_cutting(prices, n):
    dp = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(1, i + 1):
            if j < len(prices):
                candidate = prices[j] + dp[i - j]
                if candidate > dp[i]:
                    dp[i] = candidate
    return dp[n]

prices = [0, 1, 5, 8, 9, 10, 17, 17, 20]
n = 8
result = rod_cutting(prices, n)
print(f"max revenue: {result}")
