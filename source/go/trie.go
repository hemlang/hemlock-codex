package main

import "fmt"

type TrieNode struct {
	children map[rune]*TrieNode
	isEnd    bool
}

func newTrieNode() *TrieNode {
	return &TrieNode{children: make(map[rune]*TrieNode)}
}

func trieInsert(root *TrieNode, word string) {
	node := root
	for _, ch := range word {
		if node.children[ch] == nil {
			node.children[ch] = newTrieNode()
		}
		node = node.children[ch]
	}
	node.isEnd = true
}

func trieSearch(root *TrieNode, word string) bool {
	node := root
	for _, ch := range word {
		if node.children[ch] == nil {
			return false
		}
		node = node.children[ch]
	}
	return node.isEnd
}

func trieStartsWith(root *TrieNode, prefix string) bool {
	node := root
	for _, ch := range prefix {
		if node.children[ch] == nil {
			return false
		}
		node = node.children[ch]
	}
	return true
}

func main() {
	root := newTrieNode()
	words := []string{"apple", "app", "application", "bat", "ball"}
	for _, w := range words {
		trieInsert(root, w)
	}

	fmt.Printf("search \"app\": %v\n", trieSearch(root, "app"))
	fmt.Printf("search \"ap\": %v\n", trieSearch(root, "ap"))
	fmt.Printf("search \"bat\": %v\n", trieSearch(root, "bat"))
	fmt.Printf("starts_with \"app\": %v\n", trieStartsWith(root, "app"))
	fmt.Printf("starts_with \"ba\": %v\n", trieStartsWith(root, "ba"))
	fmt.Printf("starts_with \"cat\": %v\n", trieStartsWith(root, "cat"))
}
