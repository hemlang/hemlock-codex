use std::collections::VecDeque;

fn topological_sort(adj: &Vec<Vec<usize>>, n: usize) -> Vec<usize> {
    let mut in_degree = vec![0usize; n];
    for u in 0..n {
        for &v in &adj[u] {
            in_degree[v] += 1;
        }
    }
    let mut queue = VecDeque::new();
    for i in 0..n {
        if in_degree[i] == 0 {
            queue.push_back(i);
        }
    }
    let mut order = Vec::new();
    while let Some(u) = queue.pop_front() {
        order.push(u);
        for &v in &adj[u] {
            in_degree[v] -= 1;
            if in_degree[v] == 0 {
                queue.push_back(v);
            }
        }
    }
    order
}

fn main() {
    let adj = vec![vec![], vec![], vec![3], vec![1], vec![0, 1], vec![0, 2]];
    let result = topological_sort(&adj, 6);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("topological order: {}", s.join(" "));
}
