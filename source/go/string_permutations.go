package main

import "fmt"

func permutations(s string) []string {
	var results []string
	chars := []rune(s)

	var permute func(arr []rune, start int)
	permute = func(arr []rune, start int) {
		if start == len(arr)-1 {
			results = append(results, string(arr))
			return
		}
		for i := start; i < len(arr); i++ {
			arr[start], arr[i] = arr[i], arr[start]
			permute(arr, start+1)
			arr[start], arr[i] = arr[i], arr[start]
		}
	}
	permute(chars, 0)
	return results
}

func main() {
	perms := permutations("abc")
	for _, p := range perms {
		fmt.Println(p)
	}
}
