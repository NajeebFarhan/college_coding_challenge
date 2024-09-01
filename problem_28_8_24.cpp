#include <iostream>
#include <string>
#include <vector>

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

bool inArray(vector<string> elements, string str)
{
    for (string element : elements)
    {
        if (!element.compare(str))
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

        cout << "s: " << test.s << ", words: [ ";
        for (string word : test.words)
        {
            cout << word << " ";
        }
        cout << "]\n";

        cout << "Output: [ ";
        for (int o : output)
        {
            cout << o << " ";
        }
        cout << "]\n";

        cout << "Expected output: [ ";
        for (int ex : test.expected_output)
        {
            cout << ex << " ";
        }
        cout << "]\n";

        cout << "Result: " << (isEqual(output, test.expected_output) ? "pass" : "fail") << "\n";

        cout << "====================================\n\n";
    }
}