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

func inorder(root *Node, result *[]int) {
	if root == nil {
		return
	}
	inorder(root.left, result)
	*result = append(*result, root.value)
	inorder(root.right, result)
}

func main() {
	var root *Node
	values := []int{50, 30, 70, 20, 40, 60, 80}
	for _, v := range values {
		root = insert(root, v)
	}

	var result []int
	inorder(root, &result)
	parts := make([]string, len(result))
	for i, v := range result {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("inorder: %s\n", strings.Join(parts, " "))
}
