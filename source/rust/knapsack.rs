fn knapsack(weights: &[usize], values: &[i32], capacity: usize) -> i32 {
    let n = weights.len();
    let mut dp = vec![vec![0i32; capacity + 1]; n + 1];
    for i in 1..=n {
        for w in 0..=capacity {
            dp[i][w] = dp[i-1][w];
            if weights[i-1] <= w {
                let with_item = dp[i-1][w - weights[i-1]] + values[i-1];
                dp[i][w] = dp[i][w].max(with_item);
            }
        }
    }
    dp[n][capacity]
}

fn main() {
    let weights = [2, 3, 4, 5];
    let values = [3, 4, 5, 6];
    let result = knapsack(&weights, &values, 8);
    println!("max value: {}", result);
}
