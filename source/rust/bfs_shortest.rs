use std::collections::VecDeque;

fn bfs_shortest(adj: &Vec<Vec<usize>>, start: usize, end: usize, n: usize) -> (i32, Vec<usize>) {
    let mut visited = vec![false; n];
    let mut dist = vec![-1i32; n];
    let mut prev = vec![-1i64; n];
    let mut queue = VecDeque::new();
    queue.push_back(start);
    visited[start] = true;
    dist[start] = 0;

    while let Some(u) = queue.pop_front() {
        if u == end { break; }
        for &v in &adj[u] {
            if !visited[v] {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                prev[v] = u as i64;
                queue.push_back(v);
            }
        }
    }

    let mut path = Vec::new();
    let mut current = end as i64;
    while current != -1 {
        path.push(current as usize);
        current = prev[current as usize];
    }
    path.reverse();
    (dist[end], path)
}

fn main() {
    let adj = vec![
        vec![1, 2],
        vec![3],
        vec![3, 4],
        vec![5],
        vec![5],
        vec![],
    ];
    let (distance, path) = bfs_shortest(&adj, 0, 5, 6);
    println!("distance: {}", distance);
    let s: Vec<String> = path.iter().map(|x| x.to_string()).collect();
    println!("path: {}", s.join(" "));
}
