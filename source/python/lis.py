def lis(arr):
    n = len(arr)
    if n == 0:
        return 0
    dp = [1] * n
    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i] and dp[j] + 1 > dp[i]:
                dp[i] = dp[j] + 1
    return max(dp)

arr = [10, 9, 2, 5, 3, 7, 101, 18]
result = lis(arr)
print(f"lis length: {result}")
