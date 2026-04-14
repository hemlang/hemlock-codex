fn dfs(adj: &Vec<Vec<usize>>, start: usize) -> Vec<usize> {
    let n = adj.len();
    let mut visited = vec![false; n];
    let mut order = Vec::new();
    let mut stack = vec![start];

    while let Some(u) = stack.pop() {
        if visited[u] { continue; }
        visited[u] = true;
        order.push(u);
        for &v in adj[u].iter().rev() {
            if !visited[v] {
                stack.push(v);
            }
        }
    }
    order
}

fn main() {
    let adj = vec![
        vec![1, 2],
        vec![3, 4],
        vec![5],
        vec![],
        vec![5],
        vec![],
    ];
    let result = dfs(&adj, 0);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("dfs: {}", s.join(" "));
}
