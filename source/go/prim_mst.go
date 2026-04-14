package main

import "fmt"

func main() {
	const INF = 999999999
	n := 5

	adj := make([][]int, n)
	for i := 0; i < n; i++ {
		adj[i] = make([]int, n)
	}

	adj[0][1] = 2; adj[1][0] = 2
	adj[0][3] = 6; adj[3][0] = 6
	adj[1][2] = 3; adj[2][1] = 3
	adj[1][3] = 8; adj[3][1] = 8
	adj[1][4] = 5; adj[4][1] = 5
	adj[2][4] = 7; adj[4][2] = 7
	adj[3][4] = 9; adj[4][3] = 9

	inMST := make([]bool, n)
	key := make([]int, n)
	parent := make([]int, n)
	for i := 0; i < n; i++ {
		key[i] = INF
		parent[i] = -1
	}
	key[0] = 0

	for count := 0; count < n; count++ {
		u := -1
		minKey := INF
		for i := 0; i < n; i++ {
			if !inMST[i] && key[i] < minKey {
				minKey = key[i]
				u = i
			}
		}
		inMST[u] = true
		for v := 0; v < n; v++ {
			if adj[u][v] > 0 && !inMST[v] && adj[u][v] < key[v] {
				key[v] = adj[u][v]
				parent[v] = u
			}
		}
	}

	total := 0
	fmt.Println("prim MST edges:")
	for i := 1; i < n; i++ {
		fmt.Printf("  %d - %d (weight %d)\n", parent[i], i, adj[parent[i]][i])
		total += adj[parent[i]][i]
	}
	fmt.Printf("total weight: %d\n", total)
}
