package main

import "fmt"

func fibonacci(n int) int {
	memo := make(map[int]int)
	memo[0] = 0
	memo[1] = 1
	for i := 2; i <= n; i++ {
		memo[i] = memo[i-1] + memo[i-2]
	}
	return memo[n]
}

func main() {
	n := 40
	result := fibonacci(n)
	fmt.Printf("fib(%d): %d\n", n, result)
}
