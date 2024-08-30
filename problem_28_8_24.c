#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define MAX_STRING_LENGTH 100

typedef struct
{
    char data[MAX][MAX_STRING_LENGTH];
    int tail;
} Stack;

void createStack(Stack *s);
void pushStack(Stack *s, char *word);
void permute(char **s, int l, int r, Stack *stack);
int inStack(Stack stack, char *s);
int *concatentatedSubstringIndices(char *s, char **words, int string_size, int array_size);

int main()
{
    // Example input
    int n = 2;
    char *words[] = {"foo", "bar"};
    char s[] = "barfoothefoobarman";
    int *result = concatentatedSubstringIndices(s, words, strlen(s), n);

    int i = 0;
    while (1)
    {
        if (result[i] == -1)
            break;
        printf("%d ", result[i]);
        i++;
    }
}

int *concatentatedSubstringIndices(char *s, char **words, int string_size, int array_size)
{
    Stack concat_strings;
    createStack(&concat_strings);
    int *indices = (int *)malloc(string_size * sizeof(int));

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
            indices[indices_len++] = i;
        }
    }

    indices[indices_len] = -1;
    // Result
    // for (int i = 0; i < indices_len; i++)
    // {
    //     printf("%d ", indices[i]);
    // }
    // printf("\n");
    return indices;
}

void createStack(Stack *s)
{
    s->tail = -1;
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