// Matrix Chain Multiplication
function matrixChain(dims) {
    const n = dims.length - 1;
    const dp = Array.from({ length: n }, () => new Array(n).fill(0));

    for (let l = 2; l <= n; l++) {
        for (let i = 0; i <= n - l; i++) {
            const j = i + l - 1;
            dp[i][j] = 999999999;
            for (let k = i; k < j; k++) {
                const cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }
    return dp[0][n - 1];
}

const dims = [10, 30, 5, 60];
console.log(`min multiplications: ${matrixChain(dims)}`);
