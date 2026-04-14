package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	watchPath := "/tmp/hemlock_watch_test.txt"

	err := os.WriteFile(watchPath, []byte("initial content"), 0644)
	if err != nil {
		fmt.Println("write error:", err)
		return
	}
	t1 := time.Now().UnixMilli()
	fmt.Printf("[watcher] monitoring: %s\n", watchPath)
	fmt.Printf("[watcher] initial write at t=%d\n", t1)

	contents, _ := os.ReadFile(watchPath)
	fmt.Printf("[watcher] initial content: %s\n", string(contents))

	err = os.WriteFile(watchPath, []byte("modified content"), 0644)
	if err != nil {
		fmt.Println("write error:", err)
		return
	}
	t2 := time.Now().UnixMilli()
	fmt.Printf("[watcher] file modified at t=%d\n", t2)

	content, _ := os.ReadFile(watchPath)
	if string(content) == "modified content" {
		fmt.Println("[watcher] file change detected")
		fmt.Printf("[watcher] new content: %s\n", string(content))
	} else {
		fmt.Println("[watcher] no change detected")
	}

	if t2 > t1 {
		fmt.Println("[watcher] modification time advanced")
	}

	fmt.Println("[watcher] done")
}
