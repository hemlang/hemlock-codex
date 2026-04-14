package main

import "fmt"

func twoSum(nums []int, target int) (int, int) {
	m := make(map[int]int)
	for i, num := range nums {
		complement := target - num
		if j, ok := m[complement]; ok {
			return j, i
		}
		m[num] = i
	}
	return -1, -1
}

func main() {
	nums := []int{2, 7, 11, 15}
	target := 9
	i, j := twoSum(nums, target)
	fmt.Printf("indices: %d, %d\n", i, j)
}
