package main

import (
	"fmt"
	"strings"
)

func countingSort(arr []int) {
	n := len(arr)
	if n == 0 {
		return
	}
	maxVal := arr[0]
	for i := 1; i < n; i++ {
		if arr[i] > maxVal {
			maxVal = arr[i]
		}
	}
	count := make([]int, maxVal+1)
	for i := 0; i < n; i++ {
		count[arr[i]]++
	}
	idx := 0
	for i := 0; i <= maxVal; i++ {
		for count[i] > 0 {
			arr[idx] = i
			idx++
			count[i]--
		}
	}
}

func main() {
	arr := []int{64, 34, 25, 12, 22, 11, 90, 1, 45, 78}
	countingSort(arr)
	parts := make([]string, len(arr))
	for i, v := range arr {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Println(strings.Join(parts, " "))
}
