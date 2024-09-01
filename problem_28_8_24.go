package main

import (
	"fmt"
	"slices"
	"strings"
)

// * Solution
func permute(words []string, l int, r int, result *[]string) {
	if l == r {
		*result = append(*result, strings.Join(words, ""))
	} else {
		for i := l; i <= r; i++ {
			words[l], words[i] = words[i], words[l]
			permute(words, l+1, r, result)
			words[l], words[i] = words[i], words[l]
		}
	}
}

func findConcatStringIndices(s string, words []string) []int {
	var indices = make([]int, 0, 1000)
	var concatStrings = make([]string, 0, 1000)
	var concatStringLen = len(words[0]) * len(words)

	permute(words, 0, len(words)-1, &concatStrings)

	for i := 0; i < len(s)-concatStringLen+1; i++ {
		if slices.Contains(concatStrings, s[i:i+concatStringLen]) {
			indices = append(indices, i)
		}
	}
	return indices
}

// ? Tests
type Test struct {
	s               string
	words           []string
	expected_output []int
}

func isEqual(a []int, b []int) bool {
	if len(a) != len(b) {
		return false
	}

	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

func main() {
	var tests []Test = []Test{
		{
			"barfoothefoobarman",
			[]string{"foo", "bar"},
			[]int{0, 9},
		},
		{
			"wordgoodgoodgoodbestword",
			[]string{"word", "good", "best", "word"},
			[]int{},
		},
		{
			"barfoofoobarthefoobarman",
			[]string{"bar", "foo", "the"},
			[]int{6, 9, 12},
		},
	}

	for _, test := range tests {
		output := findConcatStringIndices(test.s, test.words)
		var result string
		if isEqual(output, test.expected_output) {
			result = "pass"
		} else {
			result = "fail"
		}
		fmt.Printf("s: %v, words: %v\n", test.s, test.words)
		fmt.Println("Output: ", output)
		fmt.Println("Expected output: ", test.expected_output)
		fmt.Println("Result: ", result)
		fmt.Printf("===============================\n\n")
	}
}
