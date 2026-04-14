package main

import "fmt"

// Fixed-size object pool: 8 slots of 8 bytes each
const slotSize = 8
const poolSlots = 8

var pool [poolSlots][slotSize]byte
var used [poolSlots]bool
var allocCount = 0

func poolAlloc() int {
	for i := 0; i < poolSlots; i++ {
		if !used[i] {
			used[i] = true
			allocCount++
			fmt.Printf("alloc slot %d\n", i)
			return i
		}
	}
	fmt.Println("pool exhausted!")
	return -1
}

func poolFree(slotIndex int) {
	if used[slotIndex] {
		used[slotIndex] = false
		allocCount--
		fmt.Printf("freed slot %d\n", slotIndex)
	}
}

func activeCount() int {
	count := 0
	for i := 0; i < poolSlots; i++ {
		if used[i] {
			count++
		}
	}
	return count
}

func main() {
	s0 := poolAlloc()
	s1 := poolAlloc()
	s2 := poolAlloc()
	s3 := poolAlloc()
	s4 := poolAlloc()

	// Write data (simulate ptr_write_i64)
	_ = s0
	_ = s1
	_ = s2
	_ = s3
	_ = s4

	fmt.Printf("active: %d\n", activeCount())

	poolFree(1)
	poolFree(3)

	fmt.Printf("active after free: %d\n", activeCount())

	poolAlloc()
	poolAlloc()
	poolAlloc()

	fmt.Printf("final active: %d\n", activeCount())

	fmt.Println("pool freed")
}
