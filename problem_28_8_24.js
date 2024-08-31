//* Solution
// function permute(words, l, r, result) {
//   if (l === r) {
//     result.push(words.join(""));
//   } else {
//     for (let i = l; i <= r; i++) {
//       [words[l], words[i]] = [words[i], words[l]];
//       permute(words, l + 1, r, result);
//       [words[l], words[i]] = [words[i], words[l]];
//     }
//   }
// }

// a badly written permute version of my senior, original one was in python
// writing it intentionally here
function permute(words, result, com = []) {
  if (com.length === words.length) {
    result.push(com.join(""));
    return;
  }
  words.forEach((word) => {
    if (com.every((x) => x !== word)) {
      permute(words, result, com.concat([word]));
    }
  });
}

function findConcatSubstrings(s, words) {
  let concatStrings = [],
    indices = [],
    concatStringLength = words[0].length * words.length;

  //permute(words, 0, words.length - 1, concatStrings);
  permute(words, concatStrings);

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
      output.every((value, index) => value === test.expected_output[index])
        ? "pass"
        : "fail"
    }`
  );
  console.log("========================\n");
});
