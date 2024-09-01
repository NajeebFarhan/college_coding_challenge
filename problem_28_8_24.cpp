#include <iostream>
#include <string>

#define MAX 1000

using namespace std;

template <class T>
struct Arr
{
    T data[MAX];
    int length;
};

void swap(string *a, string *b)
{
    string temp = *a;
    *a = *b;
    *b = temp;
}
void permute(Arr<string> *words, int l, int r, Arr<string> *result)
{
    if (l == r)
    {
        string buffer = "";
        for (int i = 0; i <= r; i++)
            buffer.append(words->data[i]);
        result->data[result->length++] = buffer;
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(&words->data[l], &words->data[i]);
            permute(words, l + 1, r, result);
            swap(&words->data[l], &words->data[i]);
        }
    }
}

bool inArray(Arr<string> arr, string str)
{
    for (int i = 0; i < arr.length; i++)
    {
        if (!arr.data[i].compare(str))
            return true;
    }
    return false;
}

Arr<int> findConcatSubstring(string s, Arr<string> words)
{
    Arr<int> indices;
    indices.length = 0;

    Arr<string> concatStrings;
    concatStrings.length = 0;
    int concatStringsLen = words.data[0].length() * words.length;

    permute(&words, 0, words.length - 1, &concatStrings);

    for (int i = 0; i <= s.length() - concatStringsLen; i++)
    {
        if (inArray(concatStrings, s.substr(i, concatStringsLen)))
        {
            indices.data[indices.length++] = i;
        }
    }
    return indices;
}

int main()
{
    Arr<string> words = {"foo", "bar"};
    words.length = 2;
    string s = "barfoothefoobarman";
    Arr result = findConcatSubstring(s, words);

    cout << "[ ";
    for (int i = 0; i < result.length; i++)
    {
        cout << result.data[i] << " ";
    }
    cout << "]\n";
}