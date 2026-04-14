// Coin Change Problem (Minimum Coins)
function coinChange(coins, amount) {
    const dp = new Array(amount + 1).fill(amount + 1);
    dp[0] = 0;
    for (let i = 1; i <= amount; i++) {
        for (const coin of coins) {
            if (coin <= i) {
                const candidate = dp[i - coin] + 1;
                if (candidate < dp[i]) dp[i] = candidate;
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

const coins = [1, 5, 10, 25];
const amount = 36;
console.log(`min coins: ${coinChange(coins, amount)}`);
