package main

import (
	"fmt"
	"sync"
)

func mapWorker(chunk []int, resultCh chan<- []int, wg *sync.WaitGroup) {
	defer wg.Done()
	var results []int
	for _, v := range chunk {
		results = append(results, v*v)
	}
	resultCh <- results
}

func reduceWorker(values []int) int {
	sum := 0
	for _, v := range values {
		sum += v
	}
	return sum
}

func main() {
	data := []int{1, 2, 3, 4, 5, 6, 7, 8}
	chunkSize := 2

	var chunks [][]int
	for i := 0; i < len(data); i += chunkSize {
		end := i + chunkSize
		if end > len(data) {
			end = len(data)
		}
		chunks = append(chunks, data[i:end])
	}

	resultCh := make(chan []int, len(chunks))
	var wg sync.WaitGroup

	for _, chunk := range chunks {
		wg.Add(1)
		go mapWorker(chunk, resultCh, &wg)
	}

	wg.Wait()
	close(resultCh)

	var allSquares []int
	for result := range resultCh {
		allSquares = append(allSquares, result...)
	}

	total := reduceWorker(allSquares)
	fmt.Printf("sum of squares: %d\n", total)
}
