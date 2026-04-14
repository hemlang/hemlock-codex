package main

import "fmt"

func inner() {
	defer fmt.Println("inner cleanup")
	fmt.Println("inner running")
}

func middle() {
	defer fmt.Println("middle cleanup")
	fmt.Println("middle running")
	inner()
}

func outer() {
	defer fmt.Println("outer cleanup")
	fmt.Println("outer running")
	middle()
}

func main() {
	outer()
}
