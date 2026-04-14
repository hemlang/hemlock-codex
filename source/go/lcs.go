package main

import "fmt"

func lcs(a, b string) (int, string) {
	m, n := len(a), len(b)
	dp := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]int, n+1)
	}

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if a[i-1] == b[j-1] {
				dp[i][j] = dp[i-1][j-1] + 1
			} else {
				if dp[i-1][j] >= dp[i][j-1] {
					dp[i][j] = dp[i-1][j]
				} else {
					dp[i][j] = dp[i][j-1]
				}
			}
		}
	}

	result := ""
	i, j := m, n
	for i > 0 && j > 0 {
		if a[i-1] == b[j-1] {
			result = string(a[i-1]) + result
			i--
			j--
		} else if dp[i-1][j] >= dp[i][j-1] {
			i--
		} else {
			j--
		}
	}

	return dp[m][n], result
}

func main() {
	a := "ABCBDAB"
	b := "BDCAB"
	length, subseq := lcs(a, b)
	fmt.Printf("lcs length: %d\n", length)
	fmt.Printf("lcs: %s\n", subseq)
}
