fn main() {
    let inf = 999999999i32;
    let n = 5;
    let mut adj = vec![vec![0i32; n]; n];
    adj[0][1] = 2; adj[1][0] = 2;
    adj[0][3] = 6; adj[3][0] = 6;
    adj[1][2] = 3; adj[2][1] = 3;
    adj[1][3] = 8; adj[3][1] = 8;
    adj[1][4] = 5; adj[4][1] = 5;
    adj[2][4] = 7; adj[4][2] = 7;
    adj[3][4] = 9; adj[4][3] = 9;

    let mut in_mst = vec![false; n];
    let mut key = vec![inf; n];
    let mut parent = vec![-1i32; n];
    key[0] = 0;

    for _ in 0..n {
        let u = {
            let mut best = usize::MAX;
            let mut min_k = inf;
            for i in 0..n {
                if !in_mst[i] && key[i] < min_k {
                    min_k = key[i];
                    best = i;
                }
            }
            best
        };
        in_mst[u] = true;
        for v in 0..n {
            if adj[u][v] > 0 && !in_mst[v] && adj[u][v] < key[v] {
                key[v] = adj[u][v];
                parent[v] = u as i32;
            }
        }
    }

    let mut total = 0;
    println!("prim MST edges:");
    for i in 1..n {
        let p = parent[i] as usize;
        println!("  {} - {} (weight {})", p, i, adj[p][i]);
        total += adj[p][i];
    }
    println!("total weight: {}", total);
}
