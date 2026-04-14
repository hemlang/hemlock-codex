package main

import "fmt"

func coinChange(coins []int, amount int) int {
	dp := make([]int, amount+1)
	for i := 1; i <= amount; i++ {
		dp[i] = amount + 1
	}
	dp[0] = 0

	for i := 1; i <= amount; i++ {
		for _, coin := range coins {
			if coin <= i {
				candidate := dp[i-coin] + 1
				if candidate < dp[i] {
					dp[i] = candidate
				}
			}
		}
	}

	if dp[amount] > amount {
		return -1
	}
	return dp[amount]
}

func main() {
	coins := []int{1, 5, 10, 25}
	amount := 36
	result := coinChange(coins, amount)
	fmt.Printf("min coins: %d\n", result)
}
