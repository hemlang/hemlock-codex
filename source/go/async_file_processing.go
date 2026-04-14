package main

import (
	"fmt"
	"sync"
)

type FileResult struct {
	name  string
	sum   int
	max   int
	count int
}

func processFile(name string, data []int, resultCh chan<- FileResult, wg *sync.WaitGroup) {
	defer wg.Done()
	sum := 0
	max := data[0]
	for _, v := range data {
		sum += v
		if v > max {
			max = v
		}
	}
	resultCh <- FileResult{name: name, sum: sum, max: max, count: len(data)}
}

func main() {
	type fileData struct {
		name string
		data []int
	}
	files := []fileData{
		{"data_a.csv", []int{10, 20, 30, 40, 50}},
		{"data_b.csv", []int{5, 15, 25, 35, 45, 55}},
		{"data_c.csv", []int{100, 200, 300}},
	}

	resultCh := make(chan FileResult, len(files))
	var wg sync.WaitGroup

	for _, f := range files {
		wg.Add(1)
		go processFile(f.name, f.data, resultCh, &wg)
	}

	wg.Wait()
	close(resultCh)

	results := make([]FileResult, 0, len(files))
	for r := range resultCh {
		results = append(results, r)
	}

	// Sort results by name for deterministic output
	for i := 0; i < len(results); i++ {
		for j := i + 1; j < len(results); j++ {
			if results[i].name > results[j].name {
				results[i], results[j] = results[j], results[i]
			}
		}
	}

	for _, r := range results {
		fmt.Printf("%s: sum=%d max=%d count=%d\n", r.name, r.sum, r.max, r.count)
	}
	fmt.Println("all files processed")
}
