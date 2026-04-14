// A* Pathfinding on a Grid
const ROWS = 5, COLS = 5;

const grid = [
    [0, 0, 0, 0, 0],
    [0, 1, 1, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0]
];

function heuristic(r1, c1, r2, c2) { return Math.abs(r1 - r2) + Math.abs(c1 - c2); }
function cellKey(r, c) { return r * COLS + c; }

function astar(grid, sr, sc, er, ec) {
    const INF = 999999999;
    const totalCells = ROWS * COLS;
    const gScore = new Array(totalCells).fill(INF);
    const fScore = new Array(totalCells).fill(INF);
    const cameFrom = new Array(totalCells).fill(-1);
    const closed = new Array(totalCells).fill(false);

    const startKey = cellKey(sr, sc);
    gScore[startKey] = 0;
    fScore[startKey] = heuristic(sr, sc, er, ec);
    const openList = [startKey];

    const dr = [-1, 1, 0, 0], dc = [0, 0, -1, 1];

    while (openList.length > 0) {
        let bestIdx = 0, bestF = fScore[openList[0]];
        for (let i = 1; i < openList.length; i++) {
            if (fScore[openList[i]] < bestF) { bestF = fScore[openList[i]]; bestIdx = i; }
        }

        const current = openList[bestIdx];
        openList.splice(bestIdx, 1);

        const cr = Math.floor(current / COLS), cc = current % COLS;
        if (cr === er && cc === ec) {
            const path = [];
            let c = current;
            while (c !== -1) {
                path.unshift({ r: Math.floor(c / COLS), c: c % COLS });
                c = cameFrom[c];
            }
            return path;
        }

        closed[current] = true;
        for (let d = 0; d < 4; d++) {
            const nr = cr + dr[d], nc = cc + dc[d];
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
            if (grid[nr][nc] === 1) continue;
            const nkey = cellKey(nr, nc);
            if (closed[nkey]) continue;
            const tentativeG = gScore[current] + 1;
            if (tentativeG < gScore[nkey]) {
                cameFrom[nkey] = current;
                gScore[nkey] = tentativeG;
                fScore[nkey] = tentativeG + heuristic(nr, nc, er, ec);
                if (!openList.includes(nkey)) openList.push(nkey);
            }
        }
    }
    return [];
}

const path = astar(grid, 0, 0, 4, 4);
console.log(`path length: ${path.length}`);
let coords = "";
for (let i = 0; i < path.length; i++) {
    if (i > 0) coords += " ";
    coords += `(${path[i].r},${path[i].c})`;
}
console.log(`path: ${coords}`);
