/*
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
*/

/*
More in-depth knowledge
Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"] - foobar, barfoo

Output: [0,9]

Explanation:

The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.

Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]

Output: []

Explanation:

There is no concatenated substring.

Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]

Output: [6,9,12]

Explanation:

The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"].
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"].
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"].
*/

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
