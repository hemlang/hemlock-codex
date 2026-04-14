// 0/1 Knapsack Problem
function knapsack(weights, values, capacity) {
    const n = weights.length;
    const dp = Array.from({ length: n + 1 }, () => new Array(capacity + 1).fill(0));

    for (let i = 1; i <= n; i++) {
        for (let w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                const withItem = dp[i - 1][w - weights[i - 1]] + values[i - 1];
                dp[i][w] = Math.max(dp[i][w], withItem);
            }
        }
    }
    return dp[n][capacity];
}

const weights = [2, 3, 4, 5];
const values = [3, 4, 5, 6];
const capacity = 8;
console.log(`max value: ${knapsack(weights, values, capacity)}`);
