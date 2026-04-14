package main

import (
	"fmt"
	"strings"
)

func main() {
	const INF = 999999999
	n := 4

	dist := make([][]int, n)
	for i := 0; i < n; i++ {
		dist[i] = make([]int, n)
		for j := 0; j < n; j++ {
			if i == j {
				dist[i][j] = 0
			} else {
				dist[i][j] = INF
			}
		}
	}

	dist[0][1] = 3
	dist[0][3] = 7
	dist[1][0] = 8
	dist[1][2] = 2
	dist[2][0] = 5
	dist[2][3] = 1
	dist[3][0] = 2

	for k := 0; k < n; k++ {
		for i := 0; i < n; i++ {
			for j := 0; j < n; j++ {
				if dist[i][k]+dist[k][j] < dist[i][j] {
					dist[i][j] = dist[i][k] + dist[k][j]
				}
			}
		}
	}

	fmt.Println("distance matrix:")
	for i := 0; i < n; i++ {
		var parts []string
		for j := 0; j < n; j++ {
			if dist[i][j] >= INF {
				parts = append(parts, "INF")
			} else {
				parts = append(parts, fmt.Sprintf("%d", dist[i][j]))
			}
		}
		fmt.Println(strings.Join(parts, " "))
	}
}
