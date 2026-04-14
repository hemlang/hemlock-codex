package main

import "fmt"

var cleaned = false

func cleanup() {
	cleaned = true
	fmt.Println("resource cleaned up")
}

func riskyOperation() (err error) {
	_ = make([]byte, 64)
	defer cleanup()
	defer func() {
		// simulate free
	}()
	panic("something went wrong")
}

func main() {
	func() {
		defer func() {
			if r := recover(); r != nil {
				fmt.Println("error handled")
			}
		}()
		riskyOperation()
	}()
}
