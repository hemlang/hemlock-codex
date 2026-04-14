uf_parent = []
uf_rank = []

def uf_init(n):
    global uf_parent, uf_rank
    uf_parent = list(range(n))
    uf_rank = [0] * n

def uf_find(x):
    while uf_parent[x] != x:
        uf_parent[x] = uf_parent[uf_parent[x]]
        x = uf_parent[x]
    return x

def uf_union(a, b):
    ra = uf_find(a)
    rb = uf_find(b)
    if ra == rb:
        return False
    if uf_rank[ra] < uf_rank[rb]:
        uf_parent[ra] = rb
    elif uf_rank[ra] > uf_rank[rb]:
        uf_parent[rb] = ra
    else:
        uf_parent[rb] = ra
        uf_rank[ra] += 1
    return True

n = 5
edges = [
    {"u": 0, "v": 1, "w": 2},
    {"u": 0, "v": 3, "w": 6},
    {"u": 1, "v": 2, "w": 3},
    {"u": 1, "v": 3, "w": 8},
    {"u": 1, "v": 4, "w": 5},
    {"u": 2, "v": 4, "w": 7},
    {"u": 3, "v": 4, "w": 9},
]

edges.sort(key=lambda e: e["w"])
uf_init(n)

mst_edges = []
total = 0
for edge in edges:
    if uf_union(edge["u"], edge["v"]):
        mst_edges.append(edge)
        total += edge["w"]

print("kruskal MST edges:")
for e in mst_edges:
    print(f"  {e['u']} - {e['v']} (weight {e['w']})")
print(f"total weight: {total}")
