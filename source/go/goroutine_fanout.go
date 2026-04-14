package main

import (
	"fmt"
	"sort"
	"strings"
	"sync"
)

func worker(jobs <-chan int, results chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	for j := range jobs {
		results <- j * j
	}
}

func main() {
	jobs := make(chan int, 12)
	results := make(chan int, 12)
	var wg sync.WaitGroup

	for w := 0; w < 4; w++ {
		wg.Add(1)
		go worker(jobs, results, &wg)
	}

	for i := 1; i <= 12; i++ {
		jobs <- i
	}
	close(jobs)

	wg.Wait()
	close(results)

	var collected []int
	for r := range results {
		collected = append(collected, r)
	}
	sort.Ints(collected)

	parts := make([]string, len(collected))
	for i, v := range collected {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Println(strings.Join(parts, " "))
}
