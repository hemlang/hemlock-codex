package main

import (
	"fmt"
	"strconv"
)

type Node struct {
	value string
	left  *Node
	right *Node
}

func evaluate(node *Node) int {
	if node.left == nil && node.right == nil {
		n, _ := strconv.Atoi(node.value)
		return n
	}
	leftVal := evaluate(node.left)
	rightVal := evaluate(node.right)
	switch node.value {
	case "+":
		return leftVal + rightVal
	case "-":
		return leftVal - rightVal
	case "*":
		return leftVal * rightVal
	}
	return 0
}

func main() {
	// Build: (2 + 3) * (4 - 1)
	addNode := &Node{value: "+"}
	addNode.left = &Node{value: "2"}
	addNode.right = &Node{value: "3"}

	subNode := &Node{value: "-"}
	subNode.left = &Node{value: "4"}
	subNode.right = &Node{value: "1"}

	mulNode := &Node{value: "*"}
	mulNode.left = addNode
	mulNode.right = subNode

	result := evaluate(mulNode)
	fmt.Printf("result: %d\n", result)
}
