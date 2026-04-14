package main

import (
	"fmt"
	"strings"
)

type Queue struct {
	inbox  []int
	outbox []int
}

func (q *Queue) enqueue(val int) {
	q.inbox = append(q.inbox, val)
}

func (q *Queue) dequeue() int {
	if len(q.outbox) == 0 {
		for len(q.inbox) > 0 {
			top := q.inbox[len(q.inbox)-1]
			q.inbox = q.inbox[:len(q.inbox)-1]
			q.outbox = append(q.outbox, top)
		}
	}
	val := q.outbox[len(q.outbox)-1]
	q.outbox = q.outbox[:len(q.outbox)-1]
	return val
}

func main() {
	q := &Queue{}
	q.enqueue(1)
	q.enqueue(2)
	q.enqueue(3)

	var results []string
	results = append(results, fmt.Sprintf("%d", q.dequeue()))
	results = append(results, fmt.Sprintf("%d", q.dequeue()))

	q.enqueue(4)
	q.enqueue(5)

	results = append(results, fmt.Sprintf("%d", q.dequeue()))
	results = append(results, fmt.Sprintf("%d", q.dequeue()))
	results = append(results, fmt.Sprintf("%d", q.dequeue()))

	fmt.Println(strings.Join(results, " "))
}
