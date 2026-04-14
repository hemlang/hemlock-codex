package main

import (
	"fmt"
	"sync"
)

func philosopher(id int, forks []chan int, numPhil int, resultsCh chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()

	left := id
	right := (id + 1) % numPhil

	first, second := left, right
	if left > right {
		first, second = right, left
	}

	// Pick up forks in order
	<-forks[first]
	<-forks[second]

	// Eat
	fmt.Printf("philosopher %d is eating\n", id)

	// Put down forks
	forks[first] <- 1
	forks[second] <- 1

	resultsCh <- id
}

func main() {
	numPhil := 5
	forks := make([]chan int, numPhil)
	for i := 0; i < numPhil; i++ {
		forks[i] = make(chan int, 1)
		forks[i] <- 1 // token = fork is available
	}
	resultsCh := make(chan int, numPhil)

	var wg sync.WaitGroup
	for i := 0; i < numPhil; i++ {
		wg.Add(1)
		go philosopher(i, forks, numPhil, resultsCh, &wg)
	}

	wg.Wait()

	var ids []int
	for i := 0; i < numPhil; i++ {
		ids = append(ids, <-resultsCh)
	}
	close(resultsCh)

	// Drain fork channels
	for i := 0; i < numPhil; i++ {
		<-forks[i]
		close(forks[i])
	}

	_ = ids

	fmt.Println("all philosophers ate")
}
