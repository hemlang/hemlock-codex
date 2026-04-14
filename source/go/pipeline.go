package main

import (
	"fmt"
	"strings"
)

func generate(out chan<- int) {
	for i := 1; i <= 5; i++ {
		out <- i
	}
	close(out)
}

func doubleStage(input <-chan int, output chan<- int) {
	for val := range input {
		output <- val * 2
	}
	close(output)
}

func add10Stage(input <-chan int, output chan<- int) {
	for val := range input {
		output <- val + 10
	}
	close(output)
}

func main() {
	genCh := make(chan int, 5)
	dblCh := make(chan int, 5)
	addCh := make(chan int, 5)

	go generate(genCh)
	go doubleStage(genCh, dblCh)
	go add10Stage(dblCh, addCh)

	var results []string
	for val := range addCh {
		results = append(results, fmt.Sprintf("%d", val))
	}

	fmt.Println(strings.Join(results, " "))
}
