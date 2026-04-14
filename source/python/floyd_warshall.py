INF = 999999999
n = 4

dist = [[0 if i == j else INF for j in range(n)] for i in range(n)]

dist[0][1] = 3
dist[0][3] = 7
dist[1][0] = 8
dist[1][2] = 2
dist[2][0] = 5
dist[2][3] = 1
dist[3][0] = 2

for k in range(n):
    for i in range(n):
        for j in range(n):
            if dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

print("distance matrix:")
for i in range(n):
    row_parts = []
    for j in range(n):
        if dist[i][j] >= INF:
            row_parts.append("INF")
        else:
            row_parts.append(str(dist[i][j]))
    print(" ".join(row_parts))
