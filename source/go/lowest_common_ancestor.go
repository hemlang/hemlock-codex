package main

import "fmt"

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

func lca(root *Node, p, q int) *Node {
	if root == nil {
		return nil
	}
	if p < root.value && q < root.value {
		return lca(root.left, p, q)
	}
	if p > root.value && q > root.value {
		return lca(root.right, p, q)
	}
	return root
}

func main() {
	var root *Node
	values := []int{50, 30, 70, 20, 40, 60, 80}
	for _, v := range values {
		root = insert(root, v)
	}

	r1 := lca(root, 20, 40)
	fmt.Printf("lca(20, 40): %d\n", r1.value)

	r2 := lca(root, 20, 70)
	fmt.Printf("lca(20, 70): %d\n", r2.value)

	r3 := lca(root, 60, 80)
	fmt.Printf("lca(60, 80): %d\n", r3.value)
}
