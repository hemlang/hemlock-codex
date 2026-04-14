// Rod Cutting Problem
function rodCutting(prices, n) {
    const dp = new Array(n + 1).fill(0);
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= i; j++) {
            if (j < prices.length) {
                const candidate = prices[j] + dp[i - j];
                if (candidate > dp[i]) dp[i] = candidate;
            }
        }
    }
    return dp[n];
}

const prices = [0, 1, 5, 8, 9, 10, 17, 17, 20];
const n = 8;
console.log(`max revenue: ${rodCutting(prices, n)}`);
