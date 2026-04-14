package main

import (
	"fmt"
	"strings"
)

type RingBuffer struct {
	data     []int
	capacity int
	head     int
	tail     int
	count    int
}

func newRingBuffer(capacity int) *RingBuffer {
	return &RingBuffer{
		data:     make([]int, capacity),
		capacity: capacity,
	}
}

func (rb *RingBuffer) write(val int) bool {
	if rb.count == rb.capacity {
		fmt.Printf("ring full, cannot write %d\n", val)
		return false
	}
	rb.data[rb.tail] = val
	rb.tail = (rb.tail + 1) % rb.capacity
	rb.count++
	return true
}

func (rb *RingBuffer) read() (int, bool) {
	if rb.count == 0 {
		fmt.Println("ring empty")
		return 0, false
	}
	val := rb.data[rb.head]
	rb.head = (rb.head + 1) % rb.capacity
	rb.count--
	return val, true
}

func main() {
	rb := newRingBuffer(4)

	rb.write(1)
	rb.write(2)
	rb.write(3)
	rb.write(4)

	var results []string
	if v, ok := rb.read(); ok {
		results = append(results, fmt.Sprintf("%d", v))
	}
	if v, ok := rb.read(); ok {
		results = append(results, fmt.Sprintf("%d", v))
	}

	rb.write(5)
	rb.write(6)

	for rb.count > 0 {
		if v, ok := rb.read(); ok {
			results = append(results, fmt.Sprintf("%d", v))
		}
	}

	fmt.Println(strings.Join(results, " "))
}
