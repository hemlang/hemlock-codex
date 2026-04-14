// Prim's Minimum Spanning Tree Algorithm
const INF = 999999999;
const n = 5;

const adj = Array.from({ length: n }, () => new Array(n).fill(0));
adj[0][1] = adj[1][0] = 2;
adj[0][3] = adj[3][0] = 6;
adj[1][2] = adj[2][1] = 3;
adj[1][3] = adj[3][1] = 8;
adj[1][4] = adj[4][1] = 5;
adj[2][4] = adj[4][2] = 7;
adj[3][4] = adj[4][3] = 9;

const inMst = new Array(n).fill(false);
const key = new Array(n).fill(INF);
const parent = new Array(n).fill(-1);
key[0] = 0;

for (let count = 0; count < n; count++) {
    let u = -1, minKey = INF;
    for (let i = 0; i < n; i++) {
        if (!inMst[i] && key[i] < minKey) { minKey = key[i]; u = i; }
    }
    inMst[u] = true;
    for (let v = 0; v < n; v++) {
        if (adj[u][v] > 0 && !inMst[v] && adj[u][v] < key[v]) {
            key[v] = adj[u][v];
            parent[v] = u;
        }
    }
}

let total = 0;
console.log("prim MST edges:");
for (let i = 1; i < n; i++) {
    console.log(`  ${parent[i]} - ${i} (weight ${adj[parent[i]][i]})`);
    total += adj[parent[i]][i];
}
console.log(`total weight: ${total}`);
