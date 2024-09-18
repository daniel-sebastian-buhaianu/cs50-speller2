// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Defines the size of the alphabet
// A-Z letters and apostroph character
#define ALPHABET_SIZE 27

// Represents a node in a trie
typedef struct node
{
    struct node *next[ALPHABET_SIZE + 1];
    bool end_of_word;
} node;

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
node *create_node(void);
void add_word(node *root, char *word);
void unload_trie(node *root);

#endif // DICTIONARY_H
