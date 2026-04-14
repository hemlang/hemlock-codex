package main

import (
	"fmt"
	"sync"
)

func alice(sendCh chan<- string, recvCh <-chan string, wg *sync.WaitGroup) {
	defer wg.Done()
	sendCh <- "Hi Bob! How are you?"
	msg := <-recvCh
	fmt.Printf("Alice received: %s\n", msg)

	sendCh <- "I'm working on a Hemlock project!"
	msg = <-recvCh
	fmt.Printf("Alice received: %s\n", msg)

	sendCh <- "Thanks! Talk later."
	msg = <-recvCh
	fmt.Printf("Alice received: %s\n", msg)
}

func bob(sendCh chan<- string, recvCh <-chan string, wg *sync.WaitGroup) {
	defer wg.Done()
	msg := <-recvCh
	fmt.Printf("Bob received: %s\n", msg)
	sendCh <- "Hey Alice! I'm great, you?"

	msg = <-recvCh
	fmt.Printf("Bob received: %s\n", msg)
	sendCh <- "That sounds awesome!"

	msg = <-recvCh
	fmt.Printf("Bob received: %s\n", msg)
	sendCh <- "Bye Alice!"
}

func main() {
	aliceCh := make(chan string, 10)
	bobCh := make(chan string, 10)

	var wg sync.WaitGroup
	wg.Add(2)

	go alice(bobCh, aliceCh, &wg)
	go bob(aliceCh, bobCh, &wg)

	wg.Wait()
	fmt.Println("Chat ended.")
}
