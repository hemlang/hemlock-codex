// Topological Sort (Kahn's Algorithm)
function topologicalSort(adj, n) {
    const inDegree = new Array(n).fill(0);
    for (let u = 0; u < n; u++) {
        for (const v of adj[u]) inDegree[v]++;
    }

    const queue = [];
    for (let i = 0; i < n; i++) {
        if (inDegree[i] === 0) queue.push(i);
    }

    const order = [];
    while (queue.length > 0) {
        const u = queue.shift();
        order.push(u);
        for (const v of adj[u]) {
            inDegree[v]--;
            if (inDegree[v] === 0) queue.push(v);
        }
    }
    return order;
}

const n = 6;
const adj = [[], [], [3], [1], [0, 1], [0, 2]];
const result = topologicalSort(adj, n);
console.log(`topological order: ${result.join(" ")}`);
