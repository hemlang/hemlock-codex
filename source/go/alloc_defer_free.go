package main

import "fmt"

// Simulate alloc/defer free using byte slices
func main() {
	a := make([]byte, 8)
	defer func() { a = nil }()

	b := make([]byte, 8)
	defer func() { b = nil }()

	c := make([]byte, 8)
	defer func() { c = nil }()

	// Write i32 values
	writeI32 := func(buf []byte, val int32) {
		buf[0] = byte(val)
		buf[1] = byte(val >> 8)
		buf[2] = byte(val >> 16)
		buf[3] = byte(val >> 24)
	}
	readI32 := func(buf []byte) int32 {
		return int32(buf[0]) | int32(buf[1])<<8 | int32(buf[2])<<16 | int32(buf[3])<<24
	}

	writeI32(a, 10)
	writeI32(b, 20)
	writeI32(c, 30)

	va := readI32(a)
	vb := readI32(b)
	vc := readI32(c)

	fmt.Printf("%d %d %d\n", va, vb, vc)
	fmt.Println("all memory freed")
}
