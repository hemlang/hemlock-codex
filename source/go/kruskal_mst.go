package main

import "fmt"

var ufParent []int
var ufRank []int

func ufInit(n int) {
	ufParent = make([]int, n)
	ufRank = make([]int, n)
	for i := 0; i < n; i++ {
		ufParent[i] = i
	}
}

func ufFind(x int) int {
	for ufParent[x] != x {
		ufParent[x] = ufParent[ufParent[x]]
		x = ufParent[x]
	}
	return x
}

func ufUnion(a, b int) bool {
	ra := ufFind(a)
	rb := ufFind(b)
	if ra == rb {
		return false
	}
	if ufRank[ra] < ufRank[rb] {
		ufParent[ra] = rb
	} else if ufRank[ra] > ufRank[rb] {
		ufParent[rb] = ra
	} else {
		ufParent[rb] = ra
		ufRank[ra]++
	}
	return true
}

type Edge struct {
	u, v, w int
}

func main() {
	n := 5
	edges := []Edge{
		{0, 1, 2},
		{0, 3, 6},
		{1, 2, 3},
		{1, 3, 8},
		{1, 4, 5},
		{2, 4, 7},
		{3, 4, 9},
	}

	// Insertion sort by weight
	for i := 1; i < len(edges); i++ {
		keyEdge := edges[i]
		j := i - 1
		for j >= 0 && edges[j].w > keyEdge.w {
			edges[j+1] = edges[j]
			j--
		}
		edges[j+1] = keyEdge
	}

	ufInit(n)

	var mstEdges []Edge
	total := 0

	for _, e := range edges {
		if ufUnion(e.u, e.v) {
			mstEdges = append(mstEdges, e)
			total += e.w
		}
	}

	fmt.Println("kruskal MST edges:")
	for _, e := range mstEdges {
		fmt.Printf("  %d - %d (weight %d)\n", e.u, e.v, e.w)
	}
	fmt.Printf("total weight: %d\n", total)
}
