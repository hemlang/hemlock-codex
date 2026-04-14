package main

import "fmt"

// Growing buffer that doubles when full
var capacity = 4
var size = 0
var buf []byte

func bufGrow() {
	newCap := capacity * 2
	newBuf := make([]byte, newCap)
	copy(newBuf, buf)
	buf = newBuf
	capacity = newCap
}

func writeByte(b byte) {
	if size >= capacity {
		bufGrow()
	}
	buf[size] = b
	size++
}

func readBack() string {
	return string(buf[:size])
}

func main() {
	buf = make([]byte, capacity)

	message := "Hello, World!"
	for i := 0; i < len(message); i++ {
		writeByte(message[i])
	}

	fmt.Printf("wrote %d bytes\n", size)
	fmt.Printf("capacity: %d\n", capacity)

	reconstructed := readBack()
	fmt.Printf("reconstructed: %s\n", reconstructed)
}
