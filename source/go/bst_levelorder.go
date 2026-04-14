package main

import (
	"fmt"
	"strings"
)

type Node struct {
	value int
	left  *Node
	right *Node
}

func insert(root *Node, value int) *Node {
	if root == nil {
		return &Node{value: value}
	}
	if value < root.value {
		root.left = insert(root.left, value)
	} else if value > root.value {
		root.right = insert(root.right, value)
	}
	return root
}

func levelorder(root *Node) []int {
	if root == nil {
		return []int{}
	}
	var result []int
	queue := []*Node{root}
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		result = append(result, node.value)
		if node.left != nil {
			queue = append(queue, node.left)
		}
		if node.right != nil {
			queue = append(queue, node.right)
		}
	}
	return result
}

func main() {
	var root *Node
	values := []int{50, 30, 70, 20, 40, 60, 80}
	for _, v := range values {
		root = insert(root, v)
	}

	result := levelorder(root)
	parts := make([]string, len(result))
	for i, v := range result {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("levelorder: %s\n", strings.Join(parts, " "))
}
