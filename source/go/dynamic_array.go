package main

import "fmt"

// Dynamic array that grows by doubling
var capacity = 4
var size = 0
var data []int

func grow() {
	newCap := capacity * 2
	newData := make([]int, newCap)
	copy(newData, data)
	data = newData
	capacity = newCap
}

func push(val int) {
	if size == capacity {
		grow()
	}
	data[size] = val
	size++
}

func printAll() {
	fmt.Print("values:")
	for i := 0; i < size; i++ {
		fmt.Printf(" %d", data[i])
	}
	fmt.Println()
}

func main() {
	data = make([]int, capacity)
	for i := 1; i <= 10; i++ {
		push(i)
	}
	fmt.Printf("capacity: %d\n", capacity)
	printAll()
}
