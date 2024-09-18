// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Global variables
node *trie; // the root node of the trie
int dicwords = 0; // the number of words in the dictionary

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word[0] == '\'')
    {
        return 26;
    }

    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dicfile = fopen(dictionary, "r");

    if (dicfile == NULL)
    {
        return false;
    }

    trie = create_node();

    // Read each word from the dictionary
    char word[LENGTH + 1];
    while (fgets(word, LENGTH + 1, dicfile))
    {
        // Remove the '\n' character from word
        word[strcspn(word, "\n")] = '\0';

        // Skip empty lines
        if (word[0] != '\0')
        {
            dicwords++;

            add_word(trie, word);
        }
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dicwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

// Creates a new trie node
node *create_node(void)
{
    node *p = malloc(sizeof(node));
    p->end_of_word = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        p->next[i] = NULL;
    }

    return p;
}

// Adds a new word to the trie
void add_word(node *root, char *word)
{
    node *p = root;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Create a string which contains just the word[i] character
        char ch[2];
        ch[0] = word[i];
        ch[1] = '\n';

        int index = hash(ch);

        if (p->next[index] == NULL)
        {
            p->next[index] = create_node();
        }

        p = p->next[index];
    }

    p->end_of_word = true;
}
