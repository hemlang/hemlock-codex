package main

import "fmt"

func rodCutting(prices []int, n int) int {
	dp := make([]int, n+1)
	for i := 1; i <= n; i++ {
		for j := 1; j <= i; j++ {
			if j < len(prices) {
				candidate := prices[j] + dp[i-j]
				if candidate > dp[i] {
					dp[i] = candidate
				}
			}
		}
	}
	return dp[n]
}

func main() {
	prices := []int{0, 1, 5, 8, 9, 10, 17, 17, 20}
	n := 8
	result := rodCutting(prices, n)
	fmt.Printf("max revenue: %d\n", result)
}
