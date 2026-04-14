def coin_change(coins, amount):
    dp = [amount + 1] * (amount + 1)
    dp[0] = 0
    for i in range(1, amount + 1):
        for coin in coins:
            if coin <= i:
                candidate = dp[i - coin] + 1
                if candidate < dp[i]:
                    dp[i] = candidate
    return dp[amount] if dp[amount] <= amount else -1

coins = [1, 5, 10, 25]
amount = 36
result = coin_change(coins, amount)
print(f"min coins: {result}")
