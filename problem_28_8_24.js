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

//* Solution
function permute(words, l, r, result) {
  if (l === r) {
    result.push(words.join(""));
  } else {
    for (let i = l; i <= r; i++) {
      [words[l], words[i]] = [words[i], words[l]];
      permute(words, l + 1, r, result);
      [words[l], words[i]] = [words[i], words[l]];
    }
  }
}

function findConcatSubstrings(s, words) {
  let concatStrings = [],
    indices = [],
    concatStringLength = words[0].length * words.length;

  permute(words, 0, words.length - 1, concatStrings);

  for (let i = 0; i < s.length - concatStringLength + 1; i++) {
    if (concatStrings.some((x) => x === s.slice(i, i + concatStringLength))) {
      indices.push(i);
    }
  }

  return indices;
}

//? Tests
const tests = [
  {
    s: "barfoothefoobarman",
    words: ["foo", "bar"],
    expected_output: [0, 9],
  },
  {
    s: "wordgoodgoodgoodbestword",
    words: ["word", "good", "best", "word"],
    expected_output: [],
  },
  {
    s: "barfoofoobarthefoobarman",
    words: ["bar", "foo", "the"],
    expected_output: [6, 9, 12],
  },
];

tests.forEach((test) => {
  let output = findConcatSubstrings(test.s, test.words);

  console.log(`s: ${test.s}, words: ${test.words}`);
  console.log(`Output: ${output}`);
  console.log(`Expected output: ${test.expected_output}`);
  console.log(
    `Result: ${
      output.length === test.expected_output.length &&
      output.every((value, index) => value === test.expected_output[index])
        ? "pass"
        : "fail"
    }`
  );
  console.log("========================\n");
});
