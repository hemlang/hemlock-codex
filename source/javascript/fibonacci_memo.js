// Fibonacci with Memoization (bottom-up)
function fibonacci(n) {
    const memo = { 0: 0, 1: 1 };
    for (let i = 2; i <= n; i++) memo[i] = memo[i - 1] + memo[i - 2];
    return memo[n];
}

const n = 40;
console.log(`fib(${n}): ${fibonacci(n)}`);
