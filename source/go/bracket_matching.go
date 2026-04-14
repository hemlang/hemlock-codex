package main

import "fmt"

func isBalanced(s string) bool {
	var stack []rune
	for _, c := range s {
		if c == '(' || c == '{' || c == '[' {
			stack = append(stack, c)
		} else if c == ')' || c == '}' || c == ']' {
			if len(stack) == 0 {
				return false
			}
			top := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			if c == ')' && top != '(' {
				return false
			}
			if c == '}' && top != '{' {
				return false
			}
			if c == ']' && top != '[' {
				return false
			}
		}
	}
	return len(stack) == 0
}

func main() {
	tests := []string{"({[]})", "({[}])", ""}
	for _, t := range tests {
		if isBalanced(t) {
			fmt.Printf("%q -> balanced\n", t)
		} else {
			fmt.Printf("%q -> not balanced\n", t)
		}
	}
}
