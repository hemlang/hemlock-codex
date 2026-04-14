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

func search(root *Node, value int) bool {
	if root == nil {
		return false
	}
	if value == root.value {
		return true
	}
	if value < root.value {
		return search(root.left, value)
	}
	return search(root.right, value)
}

func findMin(root *Node) *Node {
	current := root
	for current.left != nil {
		current = current.left
	}
	return current
}

func deleteNode(root *Node, value int) *Node {
	if root == nil {
		return nil
	}
	if value < root.value {
		root.left = deleteNode(root.left, value)
	} else if value > root.value {
		root.right = deleteNode(root.right, value)
	} else {
		if root.left == nil {
			return root.right
		}
		if root.right == nil {
			return root.left
		}
		successor := findMin(root.right)
		root.value = successor.value
		root.right = deleteNode(root.right, successor.value)
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

	if search(root, 40) {
		fmt.Println("search 40: found")
	} else {
		fmt.Println("search 40: not found")
	}

	if search(root, 25) {
		fmt.Println("search 25: found")
	} else {
		fmt.Println("search 25: not found")
	}

	root = deleteNode(root, 30)

	var result []int
	inorder(root, &result)
	parts := make([]string, len(result))
	for i, v := range result {
		parts[i] = fmt.Sprintf("%d", v)
	}
	fmt.Printf("inorder: %s\n", strings.Join(parts, " "))
}
