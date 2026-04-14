package main

import "fmt"

type DequeNode struct {
	val        int
	prev, next *DequeNode
}

var dqHead *DequeNode
var dqTail *DequeNode
var dqSize = 0

func pushFront(val int) {
	node := &DequeNode{val: val}
	if dqHead == nil {
		dqHead = node
		dqTail = node
	} else {
		node.next = dqHead
		dqHead.prev = node
		dqHead = node
	}
	dqSize++
	fmt.Printf("push_front: %d\n", val)
}

func pushBack(val int) {
	node := &DequeNode{val: val}
	if dqTail == nil {
		dqHead = node
		dqTail = node
	} else {
		node.prev = dqTail
		dqTail.next = node
		dqTail = node
	}
	dqSize++
	fmt.Printf("push_back: %d\n", val)
}

func popFront() (int, bool) {
	if dqHead == nil {
		fmt.Println("deque empty")
		return 0, false
	}
	node := dqHead
	val := node.val
	nxt := node.next
	if nxt != nil {
		nxt.prev = nil
	} else {
		dqTail = nil
	}
	dqHead = nxt
	dqSize--
	fmt.Printf("pop_front: %d\n", val)
	return val, true
}

func popBack() (int, bool) {
	if dqTail == nil {
		fmt.Println("deque empty")
		return 0, false
	}
	node := dqTail
	val := node.val
	prv := node.prev
	if prv != nil {
		prv.next = nil
	} else {
		dqHead = nil
	}
	dqTail = prv
	dqSize--
	fmt.Printf("pop_back: %d\n", val)
	return val, true
}

func printDeque() {
	fmt.Print("deque:")
	cur := dqHead
	for cur != nil {
		fmt.Printf(" %d", cur.val)
		cur = cur.next
	}
	fmt.Println()
}

func main() {
	pushFront(1)
	pushFront(2)
	pushBack(3)
	pushBack(4)
	printDeque()
	fmt.Printf("size: %d\n", dqSize)

	popFront()
	popBack()
	printDeque()
	fmt.Printf("size: %d\n", dqSize)

	for dqHead != nil {
		popFront()
	}
	fmt.Println("deque cleared")
}
