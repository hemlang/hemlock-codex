package main

import (
	"fmt"
	"strings"
)

func topologicalSort(adj [][]int, n int) []int {
	inDegree := make([]int, n)
	for u := 0; u < n; u++ {
		for _, v := range adj[u] {
			inDegree[v]++
		}
	}

	var queue []int
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	var order []int
	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		order = append(order, u)
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				queue = append(queue, v)
			}
		}
	}
	return order
}

func main() {
	n := 6
	adj := [][]int{{}, {}, {3}, {1}, {0, 1}, {0, 2}}

	result := topologicalSort(adj, n)
	parts := make([]string, len(result))
	for i, v := range result {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("topological order: %s\n", strings.Join(parts, " "))
}
