fn coin_change(coins: &[i32], amount: i32) -> i32 {
    let amount = amount as usize;
    let mut dp = vec![amount as i32 + 1; amount + 1];
    dp[0] = 0;
    for i in 1..=amount {
        for &coin in coins {
            if coin as usize <= i {
                let candidate = dp[i - coin as usize] + 1;
                if candidate < dp[i] { dp[i] = candidate; }
            }
        }
    }
    if dp[amount] > amount as i32 { -1 } else { dp[amount] }
}

fn main() {
    let coins = [1, 5, 10, 25];
    println!("min coins: {}", coin_change(&coins, 36));
}
