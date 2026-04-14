// Depth-First Search Traversal
function dfs(adj, start) {
    const visited = new Array(adj.length).fill(false);
    const order = [];
    const stack = [start];

    while (stack.length > 0) {
        const u = stack.pop();
        if (visited[u]) continue;
        visited[u] = true;
        order.push(u);

        const neighbors = adj[u];
        for (let i = neighbors.length - 1; i >= 0; i--) {
            if (!visited[neighbors[i]]) stack.push(neighbors[i]);
        }
    }
    return order;
}

const adj = [[1, 2], [3, 4], [5], [], [5], []];
const result = dfs(adj, 0);
console.log(`dfs: ${result.join(" ")}`);
