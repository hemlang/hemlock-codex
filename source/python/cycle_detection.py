def has_cycle(adj, n):
    color = [0] * n  # 0=white, 1=gray, 2=black

    for start in range(n):
        if color[start] != 0:
            continue
        stack = [{"node": start, "idx": 0}]
        color[start] = 1

        while stack:
            top = stack[-1]
            u = top["node"]
            neighbors = adj[u]

            if top["idx"] < len(neighbors):
                v = neighbors[top["idx"]]
                top["idx"] += 1
                if color[v] == 1:
                    return True
                if color[v] == 0:
                    color[v] = 1
                    stack.append({"node": v, "idx": 0})
            else:
                color[u] = 2
                stack.pop()

    return False

adj1 = [[1], [2], [0, 3], []]
if has_cycle(adj1, 4):
    print("graph1: cycle detected")
else:
    print("graph1: no cycle")

adj2 = [[1, 2], [3], [3], []]
if has_cycle(adj2, 4):
    print("graph2: cycle detected")
else:
    print("graph2: no cycle")
