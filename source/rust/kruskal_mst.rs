struct UnionFind {
    parent: Vec<usize>,
    rank: Vec<usize>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        UnionFind { parent: (0..n).collect(), rank: vec![0; n] }
    }
    fn find(&mut self, mut x: usize) -> usize {
        while self.parent[x] != x {
            self.parent[x] = self.parent[self.parent[x]];
            x = self.parent[x];
        }
        x
    }
    fn union(&mut self, a: usize, b: usize) -> bool {
        let ra = self.find(a);
        let rb = self.find(b);
        if ra == rb { return false; }
        if self.rank[ra] < self.rank[rb] {
            self.parent[ra] = rb;
        } else if self.rank[ra] > self.rank[rb] {
            self.parent[rb] = ra;
        } else {
            self.parent[rb] = ra;
            self.rank[ra] += 1;
        }
        true
    }
}

fn main() {
    let mut edges = vec![
        (0usize, 1usize, 2i32),
        (0, 3, 6),
        (1, 2, 3),
        (1, 3, 8),
        (1, 4, 5),
        (2, 4, 7),
        (3, 4, 9),
    ];
    edges.sort_by_key(|e| e.2);

    let mut uf = UnionFind::new(5);
    let mut mst_edges = Vec::new();
    let mut total = 0;

    for (u, v, w) in &edges {
        if uf.union(*u, *v) {
            mst_edges.push((*u, *v, *w));
            total += w;
        }
    }

    println!("kruskal MST edges:");
    for (u, v, w) in &mst_edges {
        println!("  {} - {} (weight {})", u, v, w);
    }
    println!("total weight: {}", total);
}
