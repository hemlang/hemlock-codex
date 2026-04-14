package main

import "fmt"

var urlToShort = make(map[string]string)
var shortToUrl = make(map[string]string)
var counter = 1000

func encodeID(id int) string {
	chars := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	result := ""
	n := id
	for n > 0 {
		rem := n % 62
		result = string(chars[rem]) + result
		n = (n - rem) / 62
	}
	return result
}

func shorten(url string) string {
	if short, ok := urlToShort[url]; ok {
		return short
	}
	counter++
	code := encodeID(counter)
	short := "https://sho.rt/" + code
	urlToShort[url] = short
	shortToUrl[short] = url
	return short
}

func resolve(shortURL string) string {
	if url, ok := shortToUrl[shortURL]; ok {
		return url
	}
	return ""
}

func main() {
	urls := []string{
		"https://example.com/long/path",
		"https://docs.hemlock.org/stdlib",
		"https://github.com/hemlang/42",
		"https://example.com/long/path",
	}

	fmt.Println("=== URL Shortener ===")
	for _, url := range urls {
		short := shorten(url)
		fmt.Printf("  %s\n", url)
		fmt.Printf("  -> %s\n", short)
		fmt.Println()
	}

	fmt.Println("=== Resolve Short URLs ===")
	testShort := shorten("https://docs.hemlock.org/stdlib")
	resolved := resolve(testShort)
	fmt.Printf("  %s -> %s\n", testShort, resolved)

	s1 := shorten("https://example.com/long/path")
	s2 := shorten("https://example.com/long/path")
	if s1 == s2 {
		fmt.Println("\nDuplicate URL returns same short URL: ok")
	}
}
