// Cycle Detection in Directed Graph
function hasCycle(adj, n) {
    const color = new Array(n).fill(0);

    for (let start = 0; start < n; start++) {
        if (color[start] !== 0) continue;
        const stack = [{ node: start, idx: 0 }];
        color[start] = 1;

        while (stack.length > 0) {
            const top = stack[stack.length - 1];
            const u = top.node;
            const neighbors = adj[u];

            if (top.idx < neighbors.length) {
                const v = neighbors[top.idx++];
                if (color[v] === 1) return true;
                if (color[v] === 0) {
                    color[v] = 1;
                    stack.push({ node: v, idx: 0 });
                }
            } else {
                color[u] = 2;
                stack.pop();
            }
        }
    }
    return false;
}

const adj1 = [[1], [2], [0, 3], []];
console.log(hasCycle(adj1, 4) ? "graph1: cycle detected" : "graph1: no cycle");

const adj2 = [[1, 2], [3], [3], []];
console.log(hasCycle(adj2, 4) ? "graph2: cycle detected" : "graph2: no cycle");
