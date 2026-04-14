package main

import (
	"fmt"
	"strings"
)

func producer(ch chan<- int) {
	for i := 1; i <= 10; i++ {
		ch <- i
	}
	close(ch)
}

func consumer(ch <-chan int) []int {
	var results []int
	for val := range ch {
		results = append(results, val)
	}
	return results
}

func main() {
	ch := make(chan int, 10)
	go producer(ch)
	results := consumer(ch)

	parts := make([]string, len(results))
	for i, v := range results {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("received: %s\n", strings.Join(parts, " "))
}
