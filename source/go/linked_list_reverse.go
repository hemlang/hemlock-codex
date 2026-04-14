package main

import (
	"fmt"
	"strings"
)

type Node struct {
	val  int
	next *Node
}

func buildList(arr []int) *Node {
	var head *Node
	for i := len(arr) - 1; i >= 0; i-- {
		head = &Node{val: arr[i], next: head}
	}
	return head
}

func printList(head *Node, label string) {
	var parts []string
	curr := head
	for curr != nil {
		parts = append(parts, fmt.Sprintf("%d", curr.val))
		curr = curr.next
	}
	fmt.Printf("%s: %s\n", label, strings.Join(parts, " "))
}

func reverseList(head *Node) *Node {
	var prev *Node
	curr := head
	for curr != nil {
		next := curr.next
		curr.next = prev
		prev = curr
		curr = next
	}
	return prev
}

func main() {
	head := buildList([]int{1, 2, 3, 4, 5})
	printList(head, "original")
	reversed := reverseList(head)
	printList(reversed, "reversed")
}
