package main

import (
	"fmt"
	"strings"
)

type Test struct {
	name     string
	actual   interface{}
	expected interface{}
}

var tests []Test
var passed = 0
var failed = 0

func addTest(name string, actual, expected interface{}) {
	tests = append(tests, Test{name: name, actual: actual, expected: expected})
}

func runTests() {
	fmt.Println("=== Test Results ===")
	for _, t := range tests {
		if fmt.Sprintf("%v", t.actual) == fmt.Sprintf("%v", t.expected) {
			fmt.Printf("  PASS: %s\n", t.name)
			passed++
		} else {
			fmt.Printf("  FAIL: %s (expected %v, got %v)\n", t.name, t.expected, t.actual)
			failed++
		}
	}
	total := passed + failed
	fmt.Printf("\n%d/%d tests passed\n", passed, total)
	if failed > 0 {
		fmt.Printf("%d test(s) failed\n", failed)
	}
}

func strContains(s, substr string) bool {
	return strings.Contains(s, substr)
}

func strUpper(s string) string {
	return strings.ToUpper(s)
}

func main() {
	// String tests
	addTest("string length", len("hello"), 5)
	addTest("string contains", strContains("hello world", "world"), true)
	addTest("string upper", strUpper("hello"), "HELLO")

	// Array tests
	arr := []int{1, 2, 3, 4, 5}
	addTest("array length", len(arr), 5)
	addTest("array first", arr[0], 1)
	addTest("array last", arr[len(arr)-1], 5)
	contains3 := false
	for _, v := range arr {
		if v == 3 {
			contains3 = true
			break
		}
	}
	addTest("array contains", contains3, true)

	// Math tests
	addTest("addition", 2+3, 5)
	addTest("multiplication", 6*7, 42)
	addTest("boolean logic", true && !false, true)

	runTests()
}
