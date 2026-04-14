package main

import (
	"fmt"
	"sort"
	"strings"
	"sync"
)

func worker(workCh <-chan int, resultCh chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	for val := range workCh {
		resultCh <- val * val
	}
}

func main() {
	workCh := make(chan int, 20)
	resultCh := make(chan int, 20)

	for i := 1; i <= 20; i++ {
		workCh <- i
	}
	close(workCh)

	var wg sync.WaitGroup
	for i := 0; i < 4; i++ {
		wg.Add(1)
		go worker(workCh, resultCh, &wg)
	}

	go func() {
		wg.Wait()
		close(resultCh)
	}()

	var results []int
	for val := range resultCh {
		results = append(results, val)
	}

	sort.Ints(results)
	parts := make([]string, len(results))
	for i, v := range results {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("results: %s\n", strings.Join(parts, " "))
}
