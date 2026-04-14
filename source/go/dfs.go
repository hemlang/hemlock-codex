package main

import (
	"fmt"
	"strings"
)

func dfs(adj [][]int, start int) []int {
	visited := make([]bool, len(adj))
	var order []int
	stack := []int{start}

	for len(stack) > 0 {
		u := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		if visited[u] {
			continue
		}
		visited[u] = true
		order = append(order, u)

		neighbors := adj[u]
		for i := len(neighbors) - 1; i >= 0; i-- {
			if !visited[neighbors[i]] {
				stack = append(stack, neighbors[i])
			}
		}
	}
	return order
}

func main() {
	adj := [][]int{
		{1, 2},
		{3, 4},
		{5},
		{},
		{5},
		{},
	}

	result := dfs(adj, 0)
	parts := make([]string, len(result))
	for i, v := range result {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("dfs: %s\n", strings.Join(parts, " "))
}
