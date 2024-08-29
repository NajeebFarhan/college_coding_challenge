"""
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
"""

"""
More in-depth knowledge
Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]

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
"""


#! Solution
from itertools import permutations

def solution(s: str, words: list[str]) -> list[int]:
    concatenated_strs = ["".join(i) for i in permutations(words)]
    concat_word_len = len(concatenated_strs[0])
    indices, i = [], 0
    while i + concat_word_len <= len(s):
        if s[i: i + concat_word_len] in concatenated_strs:
            indices.append(i)
        i += 1
    # indices = [i for i in range(len(s)) if i + word_len <= len(s) and s[i: i + word_len] in concatenated_strs]
    return indices



#? Tests
if __name__ == "__main__":
    tests = [
        {
            "s": "barfoothefoobarman", 
            "words": ["foo","bar"],
            "expected_output": [0,9]
        },
        {
            "s": "wordgoodgoodgoodbestword", 
            "words": ["word","good","best","word"],
            "expected_output": []
        },
        {
            "s": "barfoofoobarthefoobarman", 
            "words": ["bar","foo","the"],
            "expected_output": [6,9,12]
        }
    ]
    
    for i in tests:
        output = solution(i["s"], i["words"])
        
        print(f"s: {i["s"]}, words: {i["words"]}")
        t = ["".join(i) for i in permutations(i["words"])]
        # print("Concatenated strings", t if len(t) < 5 else f"{t[:5]}...")
        print("Output: ", output)
        print("Expected output: ", i["expected_output"])
        print("Result: ", "pass" if output == i["expected_output"] else "fail")
        print("=======================\n")
    # print(f"{[1, 2, 3]}")