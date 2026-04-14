package main

import (
	"fmt"
	"strings"
)

type Node struct {
	value  int
	left   *Node
	right  *Node
	height int
}

func height(node *Node) int {
	if node == nil {
		return 0
	}
	return node.height
}

func maxVal(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func getBalance(node *Node) int {
	if node == nil {
		return 0
	}
	return height(node.left) - height(node.right)
}

func rightRotate(y *Node) *Node {
	x := y.left
	t2 := x.right
	x.right = y
	y.left = t2
	y.height = maxVal(height(y.left), height(y.right)) + 1
	x.height = maxVal(height(x.left), height(x.right)) + 1
	return x
}

func leftRotate(x *Node) *Node {
	y := x.right
	t2 := y.left
	y.left = x
	x.right = t2
	x.height = maxVal(height(x.left), height(x.right)) + 1
	y.height = maxVal(height(y.left), height(y.right)) + 1
	return y
}

func insert(root *Node, value int) *Node {
	if root == nil {
		return &Node{value: value, height: 1}
	}
	if value < root.value {
		root.left = insert(root.left, value)
	} else if value > root.value {
		root.right = insert(root.right, value)
	} else {
		return root
	}

	root.height = maxVal(height(root.left), height(root.right)) + 1
	balance := getBalance(root)

	if balance > 1 && value < root.left.value {
		return rightRotate(root)
	}
	if balance < -1 && value > root.right.value {
		return leftRotate(root)
	}
	if balance > 1 && value > root.left.value {
		root.left = leftRotate(root.left)
		return rightRotate(root)
	}
	if balance < -1 && value < root.right.value {
		root.right = rightRotate(root.right)
		return leftRotate(root)
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
	values := []int{10, 20, 30, 40, 50, 25}
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
