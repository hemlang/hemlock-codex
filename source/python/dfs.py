def dfs(adj, start):
    visited = [False] * len(adj)
    order = []
    stack = [start]

    while stack:
        u = stack.pop()
        if visited[u]:
            continue
        visited[u] = True
        order.append(u)
        neighbors = adj[u]
        for i in range(len(neighbors) - 1, -1, -1):
            if not visited[neighbors[i]]:
                stack.append(neighbors[i])

    return order

adj = [[1, 2], [3, 4], [5], [], [5], []]
result = dfs(adj, 0)
print(f"dfs: {' '.join(str(x) for x in result)}")
