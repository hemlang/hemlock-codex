package main

import "fmt"

func main() {
	ch1 := make(chan string, 1)
	ch2 := make(chan string, 1)

	go func() {
		ch1 <- "result from channel 1"
	}()

	go func() {
		ch2 <- "result from channel 2"
	}()

	// Merge into result channel
	resultCh := make(chan string, 2)
	go func() {
		resultCh <- <-ch1
	}()
	go func() {
		resultCh <- <-ch2
	}()

	// First result that arrives (simulates select)
	msg := <-resultCh
	fmt.Printf("received: %s\n", msg)

	// Drain second
	<-resultCh
	close(resultCh)
}
