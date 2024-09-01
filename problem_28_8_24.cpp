#include <iostream>
#include <string>

#define MAX 1000

using namespace std;

void swap(string *a, string *b)
{
    string temp = *a;
    *a = *b;
    *b = temp;
}
void permute(string words[], int l, int r, string result[], int *index)
{
    if (l == r)
    {
        string buffer = "";
        for (int i = 0; i <= r; i++)
            buffer.append(words[i]);
        result[(*index)++] = buffer;
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(&words[l], &words[i]);
            permute(words, l + 1, r, result, index);
            swap(&words[l], &words[i]);
        }
    }
}

bool inArray(string arr[], int arrlen, string str)
{
    for (int i = 0; i < arrlen; i++)
    {
        if (!arr[i].compare(str))
            return true;
    }
    return false;
}

typedef struct
{
    int data[MAX];
    int length;
} Arr;
Arr findConcatSubstring(string s, string words[], int words_len)
{
    Arr indices;
    indices.length = 0;

    string concatStrings[MAX];
    int concatIndex = 0;
    int concatStringsLen = words[0].length() * words_len;

    permute(words, 0, words_len - 1, concatStrings, &concatIndex);

    for (int i = 0; i <= s.length() - concatStringsLen; i++)
    {
        if (inArray(concatStrings, concatIndex, s.substr(i, concatStringsLen)))
        {
            indices.data[indices.length++] = i;
        }
    }
    return indices;
}

int main()
{
    string words[] = {"foo", "bar"};
    string s = "barfoothefoobarman";
    Arr result = findConcatSubstring(s, words, sizeof(words) / sizeof(string));

    cout << "[ ";
    for (int i = 0; i < result.length; i++)
    {
        cout << result.data[i] << " ";
    }
    cout << "]\n";
}