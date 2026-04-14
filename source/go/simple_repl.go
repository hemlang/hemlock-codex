package main

import (
	"fmt"
	"strconv"
	"strings"
)

func tokenize(expr string) []string {
	var tokens []string
	num := ""
	for i := 0; i < len(expr); i++ {
		ch := expr[i]
		if ch == ' ' {
			if num != "" {
				tokens = append(tokens, num)
				num = ""
			}
		} else if ch == '+' || ch == '-' || ch == '*' || ch == '/' {
			if num != "" {
				tokens = append(tokens, num)
				num = ""
			}
			tokens = append(tokens, string(ch))
		} else {
			num += string(ch)
		}
	}
	if num != "" {
		tokens = append(tokens, num)
	}
	return tokens
}

func evaluate(expr string) float64 {
	tokens := tokenize(expr)
	if len(tokens) == 0 {
		return 0
	}
	result, _ := strconv.ParseFloat(tokens[0], 64)
	i := 1
	for i < len(tokens) {
		op := tokens[i]
		operand, _ := strconv.ParseFloat(tokens[i+1], 64)
		switch op {
		case "+":
			result += operand
		case "-":
			result -= operand
		case "*":
			result *= operand
		case "/":
			result /= operand
		}
		i += 2
	}
	return result
}

func main() {
	inputs := []string{
		"2 + 3",
		"10 * 4",
		"100 / 7",
		"50 - 18",
		"2 + 3 * 4",
	}

	fmt.Println("=== Simple Calculator ===")
	for _, input := range inputs {
		result := evaluate(input)
		intResult := int64(result)
		if float64(intResult) == result {
			fmt.Printf("> %s = %d\n", input, intResult)
		} else {
			// Format like Hemlock: remove trailing zeros
			s := strconv.FormatFloat(result, 'f', -1, 64)
			if strings.Contains(s, ".") {
				s = strings.TrimRight(s, "0")
				s = strings.TrimRight(s, ".")
			}
			fmt.Printf("> %s = %s\n", input, s)
		}
	}
	fmt.Println("=== Done ===")
}
