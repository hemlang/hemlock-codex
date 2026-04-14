package main

import "fmt"

const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

func b64Encode(input string) string {
	bytes := []byte(input)
	result := ""
	i := 0
	for i < len(bytes) {
		b0 := int(bytes[i])
		b1 := 0
		b2 := 0
		pad := 0

		if i+1 < len(bytes) {
			b1 = int(bytes[i+1])
		} else {
			pad = 2
		}
		if i+2 < len(bytes) {
			b2 = int(bytes[i+2])
		} else if pad == 0 {
			pad = 1
		}

		idx0 := (b0 >> 2) & 63
		idx1 := ((b0 & 3) << 4) | ((b1 >> 4) & 15)
		idx2 := ((b1 & 15) << 2) | ((b2 >> 6) & 3)
		idx3 := b2 & 63

		result += string(chars[idx0])
		result += string(chars[idx1])
		if pad == 2 {
			result += "=="
		} else if pad == 1 {
			result += string(chars[idx2]) + "="
		} else {
			result += string(chars[idx2]) + string(chars[idx3])
		}
		i += 3
	}
	return result
}

func b64CharIndex(c byte) int {
	for i := 0; i < 64; i++ {
		if chars[i] == c {
			return i
		}
	}
	return -1
}

func b64Decode(input string) string {
	var resultBytes []byte
	i := 0
	for i < len(input) {
		c0 := b64CharIndex(input[i])
		c1 := b64CharIndex(input[i+1])
		c2 := -1
		c3 := -1
		if input[i+2] != '=' {
			c2 = b64CharIndex(input[i+2])
		}
		if input[i+3] != '=' {
			c3 = b64CharIndex(input[i+3])
		}

		byte0 := byte(((c0 << 2) | ((c1 >> 4) & 3)) & 255)
		resultBytes = append(resultBytes, byte0)
		if c2 >= 0 {
			byte1 := byte((((c1 & 15) << 4) | ((c2 >> 2) & 15)) & 255)
			resultBytes = append(resultBytes, byte1)
		}
		if c3 >= 0 {
			byte2 := byte((((c2 & 3) << 6) | c3) & 255)
			resultBytes = append(resultBytes, byte2)
		}
		i += 4
	}
	return string(resultBytes)
}

func main() {
	original := "Hello, World!"
	encoded := b64Encode(original)
	fmt.Printf("original: %s\n", original)
	fmt.Printf("encoded:  %s\n", encoded)

	expected := "SGVsbG8sIFdvcmxkIQ=="
	if encoded == expected {
		fmt.Println("encoding: correct")
	} else {
		fmt.Printf("encoding: mismatch (expected %s)\n", expected)
	}

	decoded := b64Decode(encoded)
	fmt.Printf("decoded:  %s\n", decoded)

	if decoded == original {
		fmt.Println("round-trip: ok")
	} else {
		fmt.Println("round-trip: FAILED")
	}
}
