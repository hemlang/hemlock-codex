// Kruskal's Minimum Spanning Tree with Union-Find
const ufParent = [];
const ufRank = [];

function ufInit(n) {
    for (let i = 0; i < n; i++) { ufParent.push(i); ufRank.push(0); }
}

function ufFind(x) {
    while (ufParent[x] !== x) {
        ufParent[x] = ufParent[ufParent[x]];
        x = ufParent[x];
    }
    return x;
}

function ufUnion(a, b) {
    const ra = ufFind(a), rb = ufFind(b);
    if (ra === rb) return false;
    if (ufRank[ra] < ufRank[rb]) ufParent[ra] = rb;
    else if (ufRank[ra] > ufRank[rb]) ufParent[rb] = ra;
    else { ufParent[rb] = ra; ufRank[ra]++; }
    return true;
}

const n = 5;
const edges = [
    { u: 0, v: 1, w: 2 }, { u: 0, v: 3, w: 6 }, { u: 1, v: 2, w: 3 },
    { u: 1, v: 3, w: 8 }, { u: 1, v: 4, w: 5 }, { u: 2, v: 4, w: 7 },
    { u: 3, v: 4, w: 9 }
];

// Sort by weight
edges.sort((a, b) => a.w - b.w);
ufInit(n);

const mstEdges = [];
let total = 0;
for (const edge of edges) {
    if (ufUnion(edge.u, edge.v)) {
        mstEdges.push(edge);
        total += edge.w;
    }
}

console.log("kruskal MST edges:");
for (const e of mstEdges) console.log(`  ${e.u} - ${e.v} (weight ${e.w})`);
console.log(`total weight: ${total}`);
