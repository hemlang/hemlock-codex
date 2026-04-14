package main

import (
	"fmt"
	"strings"
)

func quicksort(arr []int, low, high int) {
	if low < high {
		pivot := arr[high]
		i := low - 1
		for j := low; j < high; j++ {
			if arr[j] <= pivot {
				i++
				arr[i], arr[j] = arr[j], arr[i]
			}
		}
		arr[i+1], arr[high] = arr[high], arr[i+1]
		pi := i + 1
		quicksort(arr, low, pi-1)
		quicksort(arr, pi+1, high)
	}
}

func main() {
	arr := []int{64, 34, 25, 12, 22, 11, 90, 1, 45, 78}
	quicksort(arr, 0, len(arr)-1)
	parts := make([]string, len(arr))
	for i, v := range arr {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Println(strings.Join(parts, " "))
}
