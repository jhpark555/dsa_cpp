
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node
{
    struct Node *child[26];
    bool done;
};

struct Node *create()
{
    struct Node *newnode =(struct Node*) malloc(sizeof(struct Node));
    for (int i = 0; i < 26; i++)
        newnode->child[i] = NULL;
    newnode->done = false;

    return newnode;
}

void insert(struct Node *root, char *word)
{
    struct Node *curr = root;

    while (*word)
    {
        int i = *word - 'a';
        if (curr->child[i] == NULL)
            curr->child[i] = create();
        curr = curr->child[i];
        word++;
    }
    curr->done = true;
}

bool search(struct Node *root, char *key)
{
    struct Node *curr = root;
    while (*key)
    {
        int i = *key - 'a';

        if (!curr->child[i])
            return false;
        curr = curr->child[i];
        key++;
    }
    return curr->done;
}
int main()
{
    char *keys[] = {"and", "ant", "do", "geek", "dad", "ball"};
    int n = sizeof(keys) / sizeof(keys[0]);

    struct Node *root = create();
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    // One by one search strings
    char *searchKeys[] = {"do", "ant", "bat"};
    int m = sizeof(searchKeys) / sizeof(searchKeys[0]);

    for (int i = 0; i < m; i++)
    {
        bool r = search(root, searchKeys[i]);
        printf("%d ", r);
    }

    insert(root, "hello");

    return 0;
}