package main

import "fmt"

// Manual linked list simulated with Go structs (equivalent to alloc/free pattern)
type Node struct {
	val  int
	next *Node
}

var head *Node

func push(val int) {
	head = &Node{val: val, next: head}
}

func traverse() {
	fmt.Print("list:")
	current := head
	for current != nil {
		fmt.Printf(" %d", current.val)
		current = current.next
	}
	fmt.Println()
}

func freeAll() {
	count := 0
	current := head
	for current != nil {
		next := current.next
		current = nil // allow GC
		count++
		current = next
	}
	head = nil
	fmt.Printf("freed %d nodes\n", count)
}

func main() {
	push(10)
	push(20)
	push(30)
	traverse()
	freeAll()
}
