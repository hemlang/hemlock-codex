package main

import (
	"fmt"
	"strings"
)

func bfsShortestPath(adj [][]int, start, end, n int) (int, []int) {
	visited := make([]bool, n)
	dist := make([]int, n)
	prev := make([]int, n)
	for i := range dist {
		dist[i] = -1
		prev[i] = -1
	}

	queue := []int{start}
	visited[start] = true
	dist[start] = 0

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		if u == end {
			break
		}
		for _, v := range adj[u] {
			if !visited[v] {
				visited[v] = true
				dist[v] = dist[u] + 1
				prev[v] = u
				queue = append(queue, v)
			}
		}
	}

	var path []int
	current := end
	for current != -1 {
		path = append([]int{current}, path...)
		current = prev[current]
	}

	return dist[end], path
}

func main() {
	adj := [][]int{
		{1, 2},
		{3},
		{3, 4},
		{5},
		{5},
		{},
	}

	distance, path := bfsShortestPath(adj, 0, 5, 6)
	fmt.Printf("distance: %d\n", distance)
	parts := make([]string, len(path))
	for i, v := range path {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("path: %s\n", strings.Join(parts, " "))
}
