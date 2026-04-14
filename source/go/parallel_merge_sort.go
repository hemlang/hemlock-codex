package main

import (
	"fmt"
	"strings"
)

func merge(left, right []int) []int {
	result := make([]int, 0, len(left)+len(right))
	i, j := 0, 0
	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			result = append(result, left[i])
			i++
		} else {
			result = append(result, right[j])
			j++
		}
	}
	result = append(result, left[i:]...)
	result = append(result, right[j:]...)
	return result
}

func parallelMergeSort(arr []int, resultCh chan<- []int) {
	if len(arr) <= 1 {
		resultCh <- arr
		return
	}
	mid := len(arr) / 2
	left := arr[:mid]
	right := arr[mid:]

	leftCh := make(chan []int, 1)
	rightCh := make(chan []int, 1)

	go parallelMergeSort(left, leftCh)
	go parallelMergeSort(right, rightCh)

	sortedLeft := <-leftCh
	sortedRight := <-rightCh

	resultCh <- merge(sortedLeft, sortedRight)
}

func main() {
	arr := []int{38, 27, 43, 3, 9, 82, 10, 55}
	resultCh := make(chan []int, 1)
	go parallelMergeSort(arr, resultCh)
	sorted := <-resultCh

	parts := make([]string, len(sorted))
	for i, v := range sorted {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("sorted: %s\n", strings.Join(parts, " "))
}
