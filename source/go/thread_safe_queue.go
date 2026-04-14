package main

import (
	"fmt"
	"sort"
	"strings"
	"sync"
)

func producer(id int, queue chan<- string, count int, wg *sync.WaitGroup) {
	defer wg.Done()
	for i := 0; i < count; i++ {
		queue <- fmt.Sprintf("p%d-%d", id, i)
	}
}

func consumer(queue <-chan string, expectedCount int) []string {
	var received []string
	for i := 0; i < expectedCount; i++ {
		val := <-queue
		received = append(received, val)
	}
	return received
}

func main() {
	queue := make(chan string, 100)
	numProducers := 3
	itemsPerProducer := 5
	totalItems := numProducers * itemsPerProducer

	var wg sync.WaitGroup
	resultCh := make(chan []string, 1)

	go func() {
		resultCh <- consumer(queue, totalItems)
	}()

	for i := 0; i < numProducers; i++ {
		wg.Add(1)
		go producer(i, queue, itemsPerProducer, &wg)
	}

	wg.Wait()

	results := <-resultCh
	close(queue)

	fmt.Printf("consumed %d items\n", len(results))
	sort.Strings(results)
	fmt.Printf("values: %s\n", strings.Join(results, " "))
}
