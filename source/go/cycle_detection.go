package main

import "fmt"

type frame struct {
	node int
	idx  int
}

func hasCycle(adj [][]int, n int) bool {
	color := make([]int, n)

	for start := 0; start < n; start++ {
		if color[start] != 0 {
			continue
		}
		stack := []frame{{node: start, idx: 0}}
		color[start] = 1

		for len(stack) > 0 {
			top := &stack[len(stack)-1]
			u := top.node
			neighbors := adj[u]

			if top.idx < len(neighbors) {
				v := neighbors[top.idx]
				top.idx++
				if color[v] == 1 {
					return true
				}
				if color[v] == 0 {
					color[v] = 1
					stack = append(stack, frame{node: v, idx: 0})
				}
			} else {
				color[u] = 2
				stack = stack[:len(stack)-1]
			}
		}
	}
	return false
}

func main() {
	adj1 := [][]int{{1}, {2}, {0, 3}, {}}
	if hasCycle(adj1, 4) {
		fmt.Println("graph1: cycle detected")
	} else {
		fmt.Println("graph1: no cycle")
	}

	adj2 := [][]int{{1, 2}, {3}, {3}, {}}
	if hasCycle(adj2, 4) {
		fmt.Println("graph2: cycle detected")
	} else {
		fmt.Println("graph2: no cycle")
	}
}
