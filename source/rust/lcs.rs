fn lcs(a: &str, b: &str) -> (usize, String) {
    let a: Vec<char> = a.chars().collect();
    let b: Vec<char> = b.chars().collect();
    let m = a.len();
    let n = b.len();
    let mut dp = vec![vec![0usize; n + 1]; m + 1];

    for i in 1..=m {
        for j in 1..=n {
            if a[i-1] == b[j-1] {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = dp[i-1][j].max(dp[i][j-1]);
            }
        }
    }

    let mut result = String::new();
    let mut i = m;
    let mut j = n;
    while i > 0 && j > 0 {
        if a[i-1] == b[j-1] {
            result.push(a[i-1]);
            i -= 1; j -= 1;
        } else if dp[i-1][j] >= dp[i][j-1] {
            i -= 1;
        } else {
            j -= 1;
        }
    }
    let result: String = result.chars().rev().collect();
    (dp[m][n], result)
}

fn main() {
    let (length, subseq) = lcs("ABCBDAB", "BDCAB");
    println!("lcs length: {}", length);
    println!("lcs: {}", subseq);
}
