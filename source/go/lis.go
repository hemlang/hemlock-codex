package main

import "fmt"

func lis(arr []int) int {
	n := len(arr)
	if n == 0 {
		return 0
	}
	dp := make([]int, n)
	for i := range dp {
		dp[i] = 1
	}

	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			if arr[j] < arr[i] && dp[j]+1 > dp[i] {
				dp[i] = dp[j] + 1
			}
		}
	}

	maxLen := 0
	for _, v := range dp {
		if v > maxLen {
			maxLen = v
		}
	}
	return maxLen
}

func main() {
	arr := []int{10, 9, 2, 5, 3, 7, 101, 18}
	result := lis(arr)
	fmt.Printf("lis length: %d\n", result)
}
