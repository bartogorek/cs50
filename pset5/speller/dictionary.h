// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>


// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
// number of buckets in the hashtable
#define BUCKETS 52


// define global data structures and variables
typedef struct node {
    char wrd[LENGTH + 1];                   // will hold words loaded from dictionary file
    struct node * next;                     // will hold pointer to the next item in the list
} node_t;

node_t *hashtable;                          // create an array of pointers that will store hashtable buckets


// Prototype functions
int hash(char *word);                   // hash - takes word as input and generates key (hash)
bool check(const char *word);           // check - checks if word exist in the dictionary
bool load(const char *dictionary);      // load - loads words from dictionary file into data structure
unsigned int size(void);                // size - checks size of the text file, counts words
bool unload(void);                      // unload - frees the memory previously allocated to each node


#endif // DICTIONARY_H
