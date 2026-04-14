from collections import deque

def topological_sort(adj, n):
    in_degree = [0] * n
    for u in range(n):
        for v in adj[u]:
            in_degree[v] += 1

    queue = deque()
    for i in range(n):
        if in_degree[i] == 0:
            queue.append(i)

    order = []
    while queue:
        u = queue.popleft()
        order.append(u)
        for v in adj[u]:
            in_degree[v] -= 1
            if in_degree[v] == 0:
                queue.append(v)

    return order

n = 6
adj = [[], [], [3], [1], [0, 1], [0, 2]]
result = topological_sort(adj, n)
print(f"topological order: {' '.join(str(x) for x in result)}")
