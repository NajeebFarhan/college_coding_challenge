"""
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
"""

"""
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
"""

#! Solution
# I decided to implement my own permutation function instead of using the built-in one
def permute(words: list[str], l: int, r: int, result: list[str]) -> None:
    if l == r:
        result.append("".join(words))
    else:
        for i in range(l, r + 1):
            words[l], words[i] = words[i], words[l]
            permute(words, l + 1, r, result)
            words[l], words[i] = words[i], words[l]



def concatenated_substring_indices(s: str, words: list[str]) -> list[int]:
    concatenated_strs, indices = [], []
    concat_word_len = len(words[0]) * len(words)
    
    permute(words, 0, len(words) - 1, concatenated_strs)
    
    for i in range(len(s) - concat_word_len + 1):
        if s[i: i + concat_word_len] in concatenated_strs:
            indices.append(i)
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
    
    for test in tests:
        output = concatenated_substring_indices(test["s"], test["words"])
        
        print(f"s: {test['s']}, words: {test['words']}")
        print("Output: ", output)
        print("Expected output: ", test["expected_output"])
        print("Result: ", "pass" if output == test["expected_output"] else "fail")
        print("=======================\n")