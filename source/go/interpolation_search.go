package main

import "fmt"

func interpolationSearch(arr []int, target int) int {
	low := 0
	high := len(arr) - 1

	for low <= high && target >= arr[low] && target <= arr[high] {
		if low == high {
			if arr[low] == target {
				return low
			}
			return -1
		}
		rangeVal := arr[high] - arr[low]
		pos := low + (target-arr[low])*(high-low)/rangeVal

		if arr[pos] == target {
			return pos
		} else if arr[pos] < target {
			low = pos + 1
		} else {
			high = pos - 1
		}
	}
	return -1
}

func main() {
	arr := []int{2, 5, 8, 12, 16, 23, 38, 56, 72, 91}

	result1 := interpolationSearch(arr, 23)
	if result1 != -1 {
		fmt.Printf("search 23: found at index %d\n", result1)
	} else {
		fmt.Println("search 23: not found")
	}

	result2 := interpolationSearch(arr, 50)
	if result2 != -1 {
		fmt.Printf("search 50: found at index %d\n", result2)
	} else {
		fmt.Println("search 50: not found")
	}
}
