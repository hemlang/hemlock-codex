def dijkstra(graph, start, end):
    INF = 999999999
    nodes = list(graph.keys())
    dist = {n: INF for n in nodes}
    prev = {}
    visited = set()
    dist[start] = 0

    for _ in range(len(nodes)):
        u = None
        min_dist = INF
        for node in nodes:
            if node not in visited and dist[node] < min_dist:
                min_dist = dist[node]
                u = node
        if u is None:
            break
        if u == end:
            break
        visited.add(u)
        for edge in graph[u]:
            v = edge["to"]
            alt = dist[u] + edge["weight"]
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u

    path = []
    current = end
    while current is not None:
        path.insert(0, current)
        current = prev.get(current)

    return {"dist": dist[end], "path": path}

graph = {
    "A": [{"to": "B", "weight": 4}, {"to": "C", "weight": 2}],
    "B": [{"to": "D", "weight": 3}],
    "C": [{"to": "B", "weight": 1}, {"to": "D", "weight": 5}],
    "D": [{"to": "E", "weight": 1}],
    "E": [],
}

result = dijkstra(graph, "A", "E")
print(f"shortest A->E: {result['dist']}")
print(f"path: {' '.join(result['path'])}")
