INF = 999999999
n = 5

adj = [[0] * n for _ in range(n)]
adj[0][1] = adj[1][0] = 2
adj[0][3] = adj[3][0] = 6
adj[1][2] = adj[2][1] = 3
adj[1][3] = adj[3][1] = 8
adj[1][4] = adj[4][1] = 5
adj[2][4] = adj[4][2] = 7
adj[3][4] = adj[4][3] = 9

in_mst = [False] * n
key = [INF] * n
parent = [-1] * n
key[0] = 0

for _ in range(n):
    u = -1
    min_key = INF
    for i in range(n):
        if not in_mst[i] and key[i] < min_key:
            min_key = key[i]
            u = i
    in_mst[u] = True
    for v in range(n):
        if adj[u][v] > 0 and not in_mst[v] and adj[u][v] < key[v]:
            key[v] = adj[u][v]
            parent[v] = u

total = 0
print("prim MST edges:")
for i in range(1, n):
    print(f"  {parent[i]} - {i} (weight {adj[parent[i]][i]})")
    total += adj[parent[i]][i]
print(f"total weight: {total}")
