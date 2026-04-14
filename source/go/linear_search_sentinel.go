package main

import "fmt"

func linearSearchSentinel(arr []int, target int) int {
	n := len(arr)
	last := arr[n-1]
	arr[n-1] = target

	i := 0
	for arr[i] != target {
		i++
	}

	arr[n-1] = last

	if i < n-1 {
		return i
	}
	if arr[n-1] == target {
		return n - 1
	}
	return -1
}

func main() {
	arr := []int{2, 5, 8, 12, 16, 23, 38, 56, 72, 91}

	result1 := linearSearchSentinel(arr, 23)
	if result1 != -1 {
		fmt.Printf("search 23: found at index %d\n", result1)
	} else {
		fmt.Println("search 23: not found")
	}

	result2 := linearSearchSentinel(arr, 50)
	if result2 != -1 {
		fmt.Printf("search 50: found at index %d\n", result2)
	} else {
		fmt.Println("search 50: not found")
	}
}
