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

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void swap(string *a, string *b)
{
    string temp = *a;
    *a = *b;
    *b = temp;
}
void permute(vector<string> *words, int l, int r, vector<string> *result)
{
    if (l == r)
    {
        string buffer = "";
        for (string word : *words)
            buffer.append(word);
        result->push_back(buffer);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(words->at(l), words->at(i));
            permute(words, l + 1, r, result);
            swap(words->at(l), words->at(i));
        }
    }
}

bool inArray(vector<string> arr, string str)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (!arr.at(i).compare(str))
            return true;
    }
    return false;
}

vector<int> findConcatSubstring(string s, vector<string> words)
{
    vector<int> indices;

    vector<string> concatStrings;
    int concatStringsLen = words.at(0).length() * words.size();

    permute(&words, 0, words.size() - 1, &concatStrings);

    for (int i = 0; i <= s.length() - concatStringsLen; i++)
    {
        if (inArray(concatStrings, s.substr(i, concatStringsLen)))
        {
            indices.push_back(i);
        }
    }
    return indices;
}

//? Tests
struct Test
{
    string s;
    vector<string> words;
    vector<int> expected_output;
};

bool isEqual(vector<int> a, vector<int> b)
{
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); i++)
    {
        if (a.at(i) != b.at(i))
            return false;
    }

    return true;
}

template <typename T>
string stringifyArr(vector<T> arr)
{
    string buffer = "[";
    for (int i = 0; i < arr.size(); i++)
    {
        stringstream ss;
        ss << arr[i];
        buffer += ss.str();
        if (i != arr.size() - 1)
            buffer += ", ";
    }
    buffer += "]";

    return buffer;
}

int main()
{
    Test tests[] = {
        {"barfoothefoobarman",
         {"foo", "bar"},
         {0, 9}},
        {"wordgoodgoodgoodbestword",
         {"word", "good", "best", "word"},
         {}},
        {"barfoofoobarthefoobarman",
         {"bar", "foo", "the"},
         {6, 9, 12}}};

    for (Test test : tests)
    {
        vector<int> output = findConcatSubstring(test.s, test.words);

        cout << "s: " << test.s << ", words: " << stringifyArr<string>(test.words) << "\n";

        cout << "Output: " << stringifyArr<int>(output) << "\n";

        cout << "Expected output: " << stringifyArr<int>(test.expected_output) << "\n";

        cout << "Result: " << (isEqual(output, test.expected_output) ? "pass" : "fail") << "\n";

        cout << "====================================\n\n";
    }

    return 0;
}