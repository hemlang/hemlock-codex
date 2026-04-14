use std::collections::HashMap;

fn dijkstra(graph: &HashMap<&str, Vec<(&str, i32)>>, start: &str, end: &str) -> (i32, Vec<String>) {
    let inf = 999999999i32;
    let mut dist: HashMap<&str, i32> = HashMap::new();
    let mut prev: HashMap<&str, &str> = HashMap::new();
    let mut visited: HashMap<&str, bool> = HashMap::new();
    let nodes: Vec<&str> = graph.keys().cloned().collect();

    for &node in &nodes {
        dist.insert(node, inf);
    }
    dist.insert(start, 0);

    for _ in 0..nodes.len() {
        let u = {
            let mut best: Option<&str> = None;
            let mut min_d = inf;
            for &node in &nodes {
                if !visited.get(node).copied().unwrap_or(false) {
                    let d = *dist.get(node).unwrap_or(&inf);
                    if d < min_d {
                        min_d = d;
                        best = Some(node);
                    }
                }
            }
            match best { Some(u) => u, None => break }
        };
        if u == end { break; }
        visited.insert(u, true);

        for &(v, weight) in graph.get(u).unwrap_or(&vec![]) {
            let alt = dist[u] + weight;
            if alt < *dist.get(v).unwrap_or(&inf) {
                dist.insert(v, alt);
                prev.insert(v, u);
            }
        }
    }

    let mut path = Vec::new();
    let mut current: Option<&str> = Some(end);
    while let Some(c) = current {
        path.push(c.to_string());
        current = prev.get(c).copied();
    }
    path.reverse();
    (*dist.get(end).unwrap_or(&inf), path)
}

fn main() {
    let mut graph: HashMap<&str, Vec<(&str, i32)>> = HashMap::new();
    graph.insert("A", vec![("B", 4), ("C", 2)]);
    graph.insert("B", vec![("D", 3)]);
    graph.insert("C", vec![("B", 1), ("D", 5)]);
    graph.insert("D", vec![("E", 1)]);
    graph.insert("E", vec![]);

    let (dist, path) = dijkstra(&graph, "A", "E");
    println!("shortest A->E: {}", dist);
    println!("path: {}", path.join(" "));
}
