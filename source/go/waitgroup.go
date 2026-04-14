package main

import (
	"fmt"
	"sync"
)

func doTask(id int, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Printf("task %d done\n", id)
}

func main() {
	var wg sync.WaitGroup
	for i := 1; i <= 5; i++ {
		wg.Add(1)
		go doTask(i, &wg)
	}
	wg.Wait()
	fmt.Println("all 5 tasks done")
}
