package main

import (
	"errors"
	"fmt"
)

func divide(a, b float64) (float64, error) {
	if b == 0 {
		return 0, errors.New("division by zero")
	}
	return a / b, nil
}

func parsePositive(s string) (int, error) {
	n := 0
	for _, ch := range s {
		if ch < '0' || ch > '9' {
			return 0, fmt.Errorf("invalid character: %c", ch)
		}
		n = n*10 + int(ch-'0')
	}
	if n <= 0 {
		return 0, errors.New("must be positive")
	}
	return n, nil
}

func main() {
	if result, err := divide(10, 3); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("10 / 3 = %.2f\n", result)
	}

	if _, err := divide(10, 0); err != nil {
		fmt.Println("error:", err)
	}

	if n, err := parsePositive("42"); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("parsed: %d\n", n)
	}

	if _, err := parsePositive("12x4"); err != nil {
		fmt.Println("error:", err)
	}
}
