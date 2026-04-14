fn fibonacci(n: usize) -> u64 {
    let mut memo = vec![0u64; n + 1];
    memo[0] = 0;
    if n >= 1 { memo[1] = 1; }
    for i in 2..=n {
        memo[i] = memo[i-1] + memo[i-2];
    }
    memo[n]
}

fn main() {
    let n = 40;
    println!("fib({}): {}", n, fibonacci(n));
}
