ROWS = 5
COLS = 5

grid = [
    [0, 0, 0, 0, 0],
    [0, 1, 1, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0],
]

def heuristic(r1, c1, r2, c2):
    return abs(r1 - r2) + abs(c1 - c2)

def cell_key(r, c):
    return r * COLS + c

def astar(grid, sr, sc, er, ec):
    INF = 999999999
    total_cells = ROWS * COLS
    g_score = [INF] * total_cells
    f_score = [INF] * total_cells
    came_from = [-1] * total_cells
    closed = [False] * total_cells

    start_key = cell_key(sr, sc)
    g_score[start_key] = 0
    f_score[start_key] = heuristic(sr, sc, er, ec)
    open_list = [start_key]

    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]

    while open_list:
        best_idx = 0
        best_f = f_score[open_list[0]]
        for i in range(1, len(open_list)):
            if f_score[open_list[i]] < best_f:
                best_f = f_score[open_list[i]]
                best_idx = i

        current = open_list.pop(best_idx)
        cr = current // COLS
        cc = current % COLS

        if cr == er and cc == ec:
            path = []
            c = current
            while c != -1:
                pr = c // COLS
                pc = c % COLS
                path.insert(0, {"r": pr, "c": pc})
                c = came_from[c]
            return path

        closed[current] = True

        for d in range(4):
            nr = cr + dr[d]
            nc = cc + dc[d]
            if nr < 0 or nr >= ROWS or nc < 0 or nc >= COLS:
                continue
            if grid[nr][nc] == 1:
                continue
            nkey = cell_key(nr, nc)
            if closed[nkey]:
                continue
            tentative_g = g_score[current] + 1
            if tentative_g < g_score[nkey]:
                came_from[nkey] = current
                g_score[nkey] = tentative_g
                f_score[nkey] = tentative_g + heuristic(nr, nc, er, ec)
                if nkey not in open_list:
                    open_list.append(nkey)

    return []

path = astar(grid, 0, 0, 4, 4)
print(f"path length: {len(path)}")
coords = " ".join(f"({p['r']},{p['c']})" for p in path)
print(f"path: {coords}")
