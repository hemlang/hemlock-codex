fn rod_cutting(prices: &[i32], n: usize) -> i32 {
    let mut dp = vec![0i32; n + 1];
    for i in 1..=n {
        for j in 1..=i {
            if j < prices.len() {
                let candidate = prices[j] + dp[i - j];
                if candidate > dp[i] { dp[i] = candidate; }
            }
        }
    }
    dp[n]
}

fn main() {
    let prices = [0, 1, 5, 8, 9, 10, 17, 17, 20];
    println!("max revenue: {}", rod_cutting(&prices, 8));
}
