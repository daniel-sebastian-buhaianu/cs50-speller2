// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Global variables
TrieNode *trie; // the root node of the trie
int dicwords = 0; // the number of words in the dictionary

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    TrieNode *p = trie;
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char ch[2];
        ch[0] = word[i];
        ch[1] = '\0';
        int index = hash(ch);

        if (p->children[index] == NULL)
        {
            return false;
        }

        p = p->children[index];
    }
    
    return p->is_end_of_word;
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

    trie = create_trie_node();

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

            add_word_to_trie(trie, word);
        }
    }

    fclose(dicfile);
    
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
    if (trie != NULL)
    {
        unload_trie(trie);

        return true;
    }
    else
    {
        return false;
    }
}

// Creates a new trie node
TrieNode *create_trie_node(void)
{
    TrieNode *p = malloc(sizeof(TrieNode));

    p->is_end_of_word = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        p->children[i] = NULL;
    }

    return p;
}

// Adds a new word to the trie
void add_word_to_trie(TrieNode *root, char *word)
{
    TrieNode *p = root;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char ch[2];
        ch[0] = word[i];
        ch[1] = '\0';
        int index = hash(ch);

        if (p->children[index] == NULL)
        {
            p->children[index] = create_trie_node();
        }

        p = p->children[index];
    }

    p->is_end_of_word = true;
}

// Unloads all trie nodes from memory
void unload_trie(TrieNode *node)
{
    // Handle base case
    if (node == NULL)
    {
        return;
    }

    // Free memory for all nodes in trie recursively
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        unload_trie(node->children[i]);
    }

    free(node);
}
