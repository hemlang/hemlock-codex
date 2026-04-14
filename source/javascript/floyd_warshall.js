// Floyd-Warshall All-Pairs Shortest Paths
const INF = 999999999;
const n = 4;

const dist = [];
for (let i = 0; i < n; i++) {
    const row = [];
    for (let j = 0; j < n; j++) row.push(i === j ? 0 : INF);
    dist.push(row);
}

dist[0][1] = 3; dist[0][3] = 7;
dist[1][0] = 8; dist[1][2] = 2;
dist[2][0] = 5; dist[2][3] = 1;
dist[3][0] = 2;

for (let k = 0; k < n; k++) {
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

console.log("distance matrix:");
for (let i = 0; i < n; i++) {
    let rowStr = "";
    for (let j = 0; j < n; j++) {
        if (j > 0) rowStr += " ";
        rowStr += dist[i][j] >= INF ? "INF" : `${dist[i][j]}`;
    }
    console.log(rowStr);
}
