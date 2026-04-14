const ROWS: usize = 5;
const COLS: usize = 5;

fn heuristic(r1: usize, c1: usize, r2: usize, c2: usize) -> i32 {
    ((r1 as i32 - r2 as i32).abs() + (c1 as i32 - c2 as i32).abs())
}

fn astar(grid: &[[i32; COLS]; ROWS], sr: usize, sc: usize, er: usize, ec: usize) -> Vec<(usize, usize)> {
    let inf = 999999999i32;
    let total = ROWS * COLS;
    let mut g_score = vec![inf; total];
    let mut f_score = vec![inf; total];
    let mut came_from = vec![-1i32; total];
    let mut closed = vec![false; total];

    let start_key = sr * COLS + sc;
    g_score[start_key] = 0;
    f_score[start_key] = heuristic(sr, sc, er, ec);
    let mut open_list: Vec<usize> = vec![start_key];

    let dr: [i32; 4] = [-1, 1, 0, 0];
    let dc: [i32; 4] = [0, 0, -1, 1];

    while !open_list.is_empty() {
        let best_idx = open_list.iter().enumerate()
            .min_by_key(|&(_, &k)| f_score[k]).map(|(i, _)| i).unwrap();
        let current = open_list.remove(best_idx);

        let cr = current / COLS;
        let cc = current % COLS;

        if cr == er && cc == ec {
            let mut path = Vec::new();
            let mut c = current as i32;
            while c != -1 {
                let pr = c as usize / COLS;
                let pc = c as usize % COLS;
                path.push((pr, pc));
                c = came_from[c as usize];
            }
            path.reverse();
            return path;
        }

        closed[current] = true;

        for d in 0..4 {
            let nr = cr as i32 + dr[d];
            let nc = cc as i32 + dc[d];
            if nr < 0 || nr >= ROWS as i32 || nc < 0 || nc >= COLS as i32 { continue; }
            let nr = nr as usize;
            let nc = nc as usize;
            if grid[nr][nc] == 1 { continue; }
            let nkey = nr * COLS + nc;
            if closed[nkey] { continue; }
            let tentative_g = g_score[current] + 1;
            if tentative_g < g_score[nkey] {
                came_from[nkey] = current as i32;
                g_score[nkey] = tentative_g;
                f_score[nkey] = tentative_g + heuristic(nr, nc, er, ec);
                if !open_list.contains(&nkey) {
                    open_list.push(nkey);
                }
            }
        }
    }
    vec![]
}

fn main() {
    let grid = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0],
        [0, 0, 1, 0, 0],
        [0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0],
    ];
    let path = astar(&grid, 0, 0, 4, 4);
    println!("path length: {}", path.len());
    let coords: Vec<String> = path.iter().map(|&(r, c)| format!("({},{})", r, c)).collect();
    println!("path: {}", coords.join(" "));
}
