fn main() {
    let inf = 999999999i64;
    let n = 4;
    let mut dist = vec![vec![inf; n]; n];
    for i in 0..n { dist[i][i] = 0; }

    dist[0][1] = 3; dist[0][3] = 7;
    dist[1][0] = 8; dist[1][2] = 2;
    dist[2][0] = 5; dist[2][3] = 1;
    dist[3][0] = 2;

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                if dist[i][k] != inf && dist[k][j] != inf {
                    if dist[i][k] + dist[k][j] < dist[i][j] {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    println!("distance matrix:");
    for i in 0..n {
        let row: Vec<String> = dist[i].iter().map(|&x| {
            if x >= inf { "INF".to_string() } else { x.to_string() }
        }).collect();
        println!("{}", row.join(" "));
    }
}
