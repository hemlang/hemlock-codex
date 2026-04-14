package main

import (
	"fmt"
	"os"
)

func main() {
	path := "/tmp/hemlock_defer_test.txt"
	err := os.WriteFile(path, []byte("hello from defer"), 0644)
	if err != nil {
		fmt.Println("write error:", err)
		return
	}

	f, err := os.Open(path)
	if err != nil {
		fmt.Println("open error:", err)
		return
	}
	defer f.Close()

	contents, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("read error:", err)
		return
	}

	if string(contents) == "hello from defer" {
		fmt.Println("wrote and read back successfully")
	}
}
