// Longest Increasing Subsequence (LIS)
function lis(arr) {
    const n = arr.length;
    if (n === 0) return 0;
    const dp = new Array(n).fill(1);
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }
    }
    return Math.max(...dp);
}

const arr = [10, 9, 2, 5, 3, 7, 101, 18];
console.log(`lis length: ${lis(arr)}`);
