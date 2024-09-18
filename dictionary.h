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

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE + 1];
    bool is_end_of_word;
} TrieNode;

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
TrieNode *create_trie_node(void);
void add_word_to_trie(TrieNode *root, char *word);
void unload_trie(TrieNode *node);

#endif // DICTIONARY_H
