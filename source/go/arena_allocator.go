package main

import "fmt"

// Simple bump allocator from a large backing byte slice
const arenaSize = 1024

var arena = make([]byte, arenaSize)
var offset = 0

func arenaAlloc(size int) []byte {
	if offset+size > arenaSize {
		fmt.Println("arena out of memory!")
		return nil
	}
	p := arena[offset : offset+size]
	offset += size
	return p
}

func arenaReset() {
	offset = 0
}

// Write/read i32 into a byte slice
func writeI32(buf []byte, val int32) {
	buf[0] = byte(val)
	buf[1] = byte(val >> 8)
	buf[2] = byte(val >> 16)
	buf[3] = byte(val >> 24)
}

func readI32(buf []byte) int32 {
	return int32(buf[0]) | int32(buf[1])<<8 | int32(buf[2])<<16 | int32(buf[3])<<24
}

func main() {
	a := arenaAlloc(4)
	b := arenaAlloc(4)
	c := arenaAlloc(4)
	d := arenaAlloc(4)
	e := arenaAlloc(4)

	writeI32(a, 100)
	writeI32(b, 200)
	writeI32(c, 300)
	writeI32(d, 400)
	writeI32(e, 500)

	fmt.Printf("slot 0: %d\n", readI32(a))
	fmt.Printf("slot 1: %d\n", readI32(b))
	fmt.Printf("slot 2: %d\n", readI32(c))
	fmt.Printf("slot 3: %d\n", readI32(d))
	fmt.Printf("slot 4: %d\n", readI32(e))

	fmt.Printf("arena used: %d bytes\n", offset)

	// Reset the whole arena at once (equivalent to free)
	arenaReset()
	fmt.Println("arena freed")
}
