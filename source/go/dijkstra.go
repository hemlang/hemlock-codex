package main

import (
	"fmt"
	"strings"
)

type Edge struct {
	to     string
	weight int
}

func dijkstra(graph map[string][]Edge, start, end string) (int, []string) {
	const INF = 999999999
	dist := make(map[string]int)
	prev := make(map[string]string)
	visited := make(map[string]bool)

	var nodes []string
	for k := range graph {
		nodes = append(nodes, k)
		dist[k] = INF
	}
	dist[start] = 0

	for i := 0; i < len(nodes); i++ {
		var u string
		minDist := INF
		for _, node := range nodes {
			if !visited[node] && dist[node] < minDist {
				minDist = dist[node]
				u = node
			}
		}
		if u == "" {
			break
		}
		if u == end {
			break
		}
		visited[u] = true

		for _, edge := range graph[u] {
			alt := dist[u] + edge.weight
			if alt < dist[edge.to] {
				dist[edge.to] = alt
				prev[edge.to] = u
			}
		}
	}

	var path []string
	current := end
	for current != "" {
		path = append([]string{current}, path...)
		if p, ok := prev[current]; ok {
			current = p
		} else {
			current = ""
		}
	}

	return dist[end], path
}

func main() {
	graph := map[string][]Edge{
		"A": {{to: "B", weight: 4}, {to: "C", weight: 2}},
		"B": {{to: "D", weight: 3}},
		"C": {{to: "B", weight: 1}, {to: "D", weight: 5}},
		"D": {{to: "E", weight: 1}},
		"E": {},
	}

	d, path := dijkstra(graph, "A", "E")
	fmt.Printf("shortest A->E: %d\n", d)
	fmt.Printf("path: %s\n", strings.Join(path, " "))
}
