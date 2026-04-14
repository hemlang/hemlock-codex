package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func barrierTask(id int, counter *int32, total int32, doneCh chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	atomic.AddInt32(counter, 1)

	// Spin-wait until all tasks have arrived
	for atomic.LoadInt32(counter) < total {
	}

	doneCh <- id
}

func main() {
	var counter int32
	doneCh := make(chan int, 4)
	numTasks := int32(4)

	var wg sync.WaitGroup
	for i := 0; i < int(numTasks); i++ {
		wg.Add(1)
		go barrierTask(i, &counter, numTasks, doneCh, &wg)
	}

	wg.Wait()

	count := 0
	for i := 0; i < int(numTasks); i++ {
		<-doneCh
		count++
	}
	close(doneCh)

	fmt.Printf("all %d tasks passed barrier\n", count)
}
