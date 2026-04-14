package main

import "fmt"

const ROWS = 5
const COLS = 5

type Cell struct {
	r, c int
}

func absVal(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func heuristic(r1, c1, r2, c2 int) int {
	return absVal(r1-r2) + absVal(c1-c2)
}

func cellKey(r, c int) int {
	return r*COLS + c
}

func astar(grid [][]int, sr, sc, er, ec int) []Cell {
	const INF = 999999999
	totalCells := ROWS * COLS

	gScore := make([]int, totalCells)
	fScore := make([]int, totalCells)
	cameFrom := make([]int, totalCells)
	closed := make([]bool, totalCells)
	for i := 0; i < totalCells; i++ {
		gScore[i] = INF
		fScore[i] = INF
		cameFrom[i] = -1
	}

	startKey := cellKey(sr, sc)
	gScore[startKey] = 0
	fScore[startKey] = heuristic(sr, sc, er, ec)

	openList := []int{startKey}

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(openList) > 0 {
		bestIdx := 0
		bestF := fScore[openList[0]]
		for i := 1; i < len(openList); i++ {
			if fScore[openList[i]] < bestF {
				bestF = fScore[openList[i]]
				bestIdx = i
			}
		}

		current := openList[bestIdx]
		openList = append(openList[:bestIdx], openList[bestIdx+1:]...)

		cr := current / COLS
		cc := current % COLS

		if cr == er && cc == ec {
			var path []Cell
			c := current
			for c != -1 {
				pr := c / COLS
				pc := c % COLS
				path = append([]Cell{{pr, pc}}, path...)
				c = cameFrom[c]
			}
			return path
		}

		closed[current] = true

		for d := 0; d < 4; d++ {
			nr := cr + dr[d]
			nc := cc + dc[d]
			if nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS {
				continue
			}
			if grid[nr][nc] == 1 {
				continue
			}
			nkey := cellKey(nr, nc)
			if closed[nkey] {
				continue
			}
			tentativeG := gScore[current] + 1
			if tentativeG < gScore[nkey] {
				cameFrom[nkey] = current
				gScore[nkey] = tentativeG
				fScore[nkey] = tentativeG + heuristic(nr, nc, er, ec)
				found := false
				for _, k := range openList {
					if k == nkey {
						found = true
						break
					}
				}
				if !found {
					openList = append(openList, nkey)
				}
			}
		}
	}
	return nil
}

func main() {
	grid := [][]int{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0},
	}

	path := astar(grid, 0, 0, 4, 4)
	fmt.Printf("path length: %d\n", len(path))
	coords := ""
	for i, p := range path {
		if i > 0 {
			coords += " "
		}
		coords += fmt.Sprintf("(%d,%d)", p.r, p.c)
	}
	fmt.Printf("path: %s\n", coords)
}
