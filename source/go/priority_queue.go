package main

import (
	"fmt"
	"strings"
)

type MinHeap struct {
	heap []int
}

func (pq *MinHeap) insert(val int) {
	pq.heap = append(pq.heap, val)
	i := len(pq.heap) - 1
	for i > 0 {
		parent := (i - 1) / 2
		if pq.heap[i] < pq.heap[parent] {
			pq.heap[i], pq.heap[parent] = pq.heap[parent], pq.heap[i]
			i = parent
		} else {
			break
		}
	}
}

func (pq *MinHeap) extractMin() int {
	min := pq.heap[0]
	last := pq.heap[len(pq.heap)-1]
	pq.heap = pq.heap[:len(pq.heap)-1]
	if len(pq.heap) > 0 {
		pq.heap[0] = last
		i := 0
		for {
			left := 2*i + 1
			right := 2*i + 2
			smallest := i
			if left < len(pq.heap) && pq.heap[left] < pq.heap[smallest] {
				smallest = left
			}
			if right < len(pq.heap) && pq.heap[right] < pq.heap[smallest] {
				smallest = right
			}
			if smallest != i {
				pq.heap[i], pq.heap[smallest] = pq.heap[smallest], pq.heap[i]
				i = smallest
			} else {
				break
			}
		}
	}
	return min
}

func main() {
	pq := &MinHeap{}
	values := []int{5, 3, 7, 1, 4, 2}
	for _, v := range values {
		pq.insert(v)
	}

	var results []string
	for i := 0; i < 6; i++ {
		results = append(results, fmt.Sprintf("%d", pq.extractMin()))
	}
	fmt.Println(strings.Join(results, " "))
}
