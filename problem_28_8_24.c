/*
?You are given a string s and an array of strings words. All the strings of words are of the same length.

!A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

?For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
*/

/*
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
*/

#include <stdio.h>
#include <string.h>

#define MAX 1000
#define MAX_STRING_LENGTH 100

typedef struct
{
    char data[MAX][MAX_STRING_LENGTH];
    int tail;
} Stack;

typedef struct
{
    int data[MAX];
    int length;
} Array;

void createStack(Stack *s);
void createArray(Array *a);
void pushStack(Stack *s, char *word);
void permute(char **s, int l, int r, Stack *stack);
int inStack(Stack stack, char *s);
Array concatentatedSubstringIndices(char *s, char **words, int string_size, int array_size);

int main()
{
    // Example input
    int n = 2;
    char *words[] = {"foo", "bar"};
    // foobar, barfoo
    char s[] = "barfoothefoobarman";
    Array result = concatentatedSubstringIndices(s, words, strlen(s), n);

    for (int i = 0; i < result.length; i++)
    {
        printf("%d ", result.data[i]);
    }
    printf("\n");
}

Array concatentatedSubstringIndices(char *s, char **words, int string_size, int array_size)
{
    Stack concat_strings;
    createStack(&concat_strings);
    Array indices;
    createArray(&indices);

    permute(words, 0, array_size - 1, &concat_strings);
    int concat_str_len = strlen(concat_strings.data[0]);

    int indices_len = 0;
    for (int i = 0; i <= strlen(s) - concat_str_len; i++)
    {
        char temp[concat_str_len];
        for (int j = i; j < i + concat_str_len; j++)
        {
            temp[j - i] = s[j];
        }
        if (inStack(concat_strings, temp))
        {
            indices.data[indices.length++] = i;
        }
    }

    return indices;
}

void createStack(Stack *s)
{
    s->tail = -1;
}

void createArray(Array *a)
{
    a->length = 0;
}

void pushStack(Stack *s, char *word)
{
    strcpy(s->data[++s->tail], word);
}

// Function to swap two strings
void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char **s, int l, int r, Stack *stack)
{
    if (l == r)
    {
        // Join the strings and store in result
        char buffer[MAX_STRING_LENGTH] = "";
        for (int i = 0; i <= r; i++)
        {
            strcat(buffer, s[i]);
        }
        pushStack(stack, buffer);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(&s[l], &s[i]);
            permute(s, l + 1, r, stack);
            swap(&s[l], &s[i]); // backtrack
        }
    }
}

int inStack(Stack stack, char *s)
{
    for (int i = 0; i <= stack.tail; i++)
    {
        if (!strcmp(s, stack.data[i]))
            return 1;
    }
    return 0;
}