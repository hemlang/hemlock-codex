from collections import deque

def bfs_shortest(adj, start, end, n):
    visited = [False] * n
    dist = [-1] * n
    prev = [-1] * n

    queue = deque([start])
    visited[start] = True
    dist[start] = 0

    while queue:
        u = queue.popleft()
        if u == end:
            break
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                dist[v] = dist[u] + 1
                prev[v] = u
                queue.append(v)

    path = []
    current = end
    while current != -1:
        path.insert(0, current)
        current = prev[current]

    return {"distance": dist[end], "path": path}

adj = [[1, 2], [3], [3, 4], [5], [5], []]
result = bfs_shortest(adj, 0, 5, 6)
print(f"distance: {result['distance']}")
print(f"path: {' '.join(str(x) for x in result['path'])}")
