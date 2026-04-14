package main

import "fmt"

func binarySearch(arr []int, target int) int {
	low := 0
	high := len(arr) - 1
	for low <= high {
		mid := low + (high-low)/2
		if arr[mid] == target {
			return mid
		} else if arr[mid] < target {
			low = mid + 1
		} else {
			high = mid - 1
		}
	}
	return -1
}

func main() {
	arr := []int{2, 5, 8, 12, 16, 23, 38, 56, 72, 91}

	result1 := binarySearch(arr, 23)
	if result1 != -1 {
		fmt.Printf("search 23: found at index %d\n", result1)
	} else {
		fmt.Println("search 23: not found")
	}

	result2 := binarySearch(arr, 50)
	if result2 != -1 {
		fmt.Printf("search 50: found at index %d\n", result2)
	} else {
		fmt.Println("search 50: not found")
	}
}
