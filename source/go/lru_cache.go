package main

import "fmt"

type LRUNode struct {
	key        string
	val        int
	prev, next *LRUNode
}

type LRUCache struct {
	capacity int
	size     int
	m        map[string]*LRUNode
	head     *LRUNode
	tail     *LRUNode
}

func newLRU(capacity int) *LRUCache {
	head := &LRUNode{}
	tail := &LRUNode{}
	head.next = tail
	tail.prev = head
	return &LRUCache{
		capacity: capacity,
		m:        make(map[string]*LRUNode),
		head:     head,
		tail:     tail,
	}
}

func (c *LRUCache) removeNode(node *LRUNode) {
	node.prev.next = node.next
	node.next.prev = node.prev
}

func (c *LRUCache) addToFront(node *LRUNode) {
	node.next = c.head.next
	node.prev = c.head
	c.head.next.prev = node
	c.head.next = node
}

func (c *LRUCache) get(key int) {
	skey := fmt.Sprintf("%d", key)
	if node, ok := c.m[skey]; ok {
		c.removeNode(node)
		c.addToFront(node)
		fmt.Printf("get(%d) -> %d (hit)\n", key, node.val)
	} else {
		fmt.Printf("get(%d) -> miss\n", key)
	}
}

func (c *LRUCache) put(key, val int) {
	skey := fmt.Sprintf("%d", key)
	if node, ok := c.m[skey]; ok {
		node.val = val
		c.removeNode(node)
		c.addToFront(node)
		fmt.Printf("put(%d, %d) -> updated\n", key, val)
	} else {
		node := &LRUNode{key: skey, val: val}
		c.m[skey] = node
		c.addToFront(node)
		c.size++
		if c.size > c.capacity {
			evict := c.tail.prev
			c.removeNode(evict)
			delete(c.m, evict.key)
			c.size--
			fmt.Printf("put(%d, %d) -> added, evicted key %s\n", key, val, evict.key)
		} else {
			fmt.Printf("put(%d, %d) -> added\n", key, val)
		}
	}
}

func main() {
	cache := newLRU(3)
	cache.put(1, 10)
	cache.put(2, 20)
	cache.put(3, 30)
	cache.get(2)
	cache.put(4, 40)
	cache.get(1)
	cache.get(3)
	cache.get(4)
}
