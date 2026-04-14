package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func incrementWorker(counter *int32, iterations int, doneCh chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	for i := 0; i < iterations; i++ {
		atomic.AddInt32(counter, 1)
	}
	doneCh <- 1
}

func main() {
	var counter int32
	doneCh := make(chan int, 10)
	numTasks := 10
	iterations := 100

	var wg sync.WaitGroup
	for i := 0; i < numTasks; i++ {
		wg.Add(1)
		go incrementWorker(&counter, iterations, doneCh, &wg)
	}

	wg.Wait()

	for i := 0; i < numTasks; i++ {
		<-doneCh
	}
	close(doneCh)

	finalVal := atomic.LoadInt32(&counter)
	fmt.Printf("final: %d\n", finalVal)
}
