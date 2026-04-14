package main

import "fmt"

func editDistance(a, b string) int {
	m, n := len(a), len(b)
	dp := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]int, n+1)
	}

	for i := 0; i <= m; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= n; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if a[i-1] == b[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				insertOp := dp[i][j-1] + 1
				deleteOp := dp[i-1][j] + 1
				replaceOp := dp[i-1][j-1] + 1
				dp[i][j] = insertOp
				if deleteOp < dp[i][j] {
					dp[i][j] = deleteOp
				}
				if replaceOp < dp[i][j] {
					dp[i][j] = replaceOp
				}
			}
		}
	}
	return dp[m][n]
}

func main() {
	a := "kitten"
	b := "sitting"
	result := editDistance(a, b)
	fmt.Printf("edit distance: %d\n", result)
}
