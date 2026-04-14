package main

import "fmt"

func multiDefer() {
	fmt.Println("start")
	defer fmt.Println("first defer")
	defer fmt.Println("second defer")
	defer fmt.Println("third defer")
	fmt.Println("end")
}

func deferInLoop() {
	for i := 0; i < 3; i++ {
		i := i // capture loop variable
		defer fmt.Printf("loop defer %d\n", i)
	}
	fmt.Println("after loop")
}

func main() {
	multiDefer()
	fmt.Println("---")
	deferInLoop()
}
