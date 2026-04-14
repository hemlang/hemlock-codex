fn has_cycle(adj: &Vec<Vec<usize>>, n: usize) -> bool {
    let mut color = vec![0u8; n]; // 0=white, 1=gray, 2=black

    for start in 0..n {
        if color[start] != 0 { continue; }
        let mut stack: Vec<(usize, usize)> = vec![(start, 0)];
        color[start] = 1;

        while let Some(top) = stack.last_mut() {
            let u = top.0;
            let idx = top.1;
            let neighbors = &adj[u];

            if idx < neighbors.len() {
                let v = neighbors[idx];
                stack.last_mut().unwrap().1 += 1;
                if color[v] == 1 { return true; }
                if color[v] == 0 {
                    color[v] = 1;
                    stack.push((v, 0));
                }
            } else {
                color[u] = 2;
                stack.pop();
            }
        }
    }
    false
}

fn main() {
    let adj1 = vec![vec![1], vec![2], vec![0, 3], vec![]];
    if has_cycle(&adj1, 4) { println!("graph1: cycle detected"); } else { println!("graph1: no cycle"); }

    let adj2 = vec![vec![1, 2], vec![3], vec![3], vec![]];
    if has_cycle(&adj2, 4) { println!("graph2: cycle detected"); } else { println!("graph2: no cycle"); }
}
