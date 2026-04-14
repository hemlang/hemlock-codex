// BFS Shortest Path (Unweighted)
function bfsShort(adj, start, end, n) {
    const visited = new Array(n).fill(false);
    const dist = new Array(n).fill(-1);
    const prev = new Array(n).fill(-1);

    const queue = [start];
    visited[start] = true;
    dist[start] = 0;

    while (queue.length > 0) {
        const u = queue.shift();
        if (u === end) break;
        for (const v of adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                prev[v] = u;
                queue.push(v);
            }
        }
    }

    const path = [];
    let current = end;
    while (current !== -1) {
        path.unshift(current);
        current = prev[current];
    }

    return { distance: dist[end], path };
}

const adj = [[1, 2], [3], [3, 4], [5], [5], []];
const result = bfsShort(adj, 0, 5, 6);
console.log(`distance: ${result.distance}`);
console.log(`path: ${result.path.join(" ")}`);
