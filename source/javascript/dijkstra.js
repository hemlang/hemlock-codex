// Dijkstra's Shortest Path Algorithm
function dijkstra(graph, start, end) {
    const dist = new Map();
    const prev = new Map();
    const visited = new Set();
    const nodes = [...graph.keys()];

    for (const node of nodes) dist.set(node, 999999999);
    dist.set(start, 0);

    for (let i = 0; i < nodes.length; i++) {
        let u = null, minDist = 999999999;
        for (const node of nodes) {
            if (!visited.has(node) && dist.get(node) < minDist) {
                minDist = dist.get(node);
                u = node;
            }
        }

        if (u === null) break;
        if (u === end) break;
        visited.add(u);

        for (const edge of graph.get(u)) {
            const alt = dist.get(u) + edge.weight;
            if (alt < dist.get(edge.to)) {
                dist.set(edge.to, alt);
                prev.set(edge.to, u);
            }
        }
    }

    const path = [];
    let current = end;
    while (current !== null && current !== undefined) {
        path.unshift(current);
        current = prev.has(current) ? prev.get(current) : null;
    }

    return { dist: dist.get(end), path };
}

const graph = new Map();
graph.set("A", [{ to: "B", weight: 4 }, { to: "C", weight: 2 }]);
graph.set("B", [{ to: "D", weight: 3 }]);
graph.set("C", [{ to: "B", weight: 1 }, { to: "D", weight: 5 }]);
graph.set("D", [{ to: "E", weight: 1 }]);
graph.set("E", []);

const result = dijkstra(graph, "A", "E");
console.log(`shortest A->E: ${result.dist}`);
console.log(`path: ${result.path.join(" ")}`);
