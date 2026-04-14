fn matrix_chain(dims: &[usize]) -> usize {
    let n = dims.len() - 1;
    let mut dp = vec![vec![0usize; n]; n];
    for l in 2..=n {
        for i in 0..=n - l {
            let j = i + l - 1;
            dp[i][j] = usize::MAX;
            for k in i..j {
                let cost = dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
                if cost < dp[i][j] { dp[i][j] = cost; }
            }
        }
    }
    dp[0][n-1]
}

fn main() {
    let dims = [10, 30, 5, 60];
    println!("min multiplications: {}", matrix_chain(&dims));
}
