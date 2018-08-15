// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


// HELPER functions
// hash function
int hash(char *word)
{
    int key = word[0];              // first character of the string
    int length = strlen(word) % 2;  // check if number of characters in string is even or odd

    if (key < 97)                   // in case the first character is uppercase
        key += 32;                  // convert to lowercase

    key -= 97;                      // reduce the number by 97 therefore making it between 0 and 25

    if (length == 1)                // if the number of characters in the string is odd
        key += 26;                  // add 26 therefore making it between 26 - 51 (allows me to increase numnber of buckets to 52)

    return key;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // declare variables
    int len = strlen(word);                         // check length of string passed in as argument
    char wd[len + 1];                               // declare pointer to string that will store 'word'
    strcpy(wd, word);                               // copy value of function argument into local string (runs faster)
    int key = hash(wd);                             // hash the input word to establish key (bucket number)
    node_t *temp = (hashtable+key)->next;           // create node pointer and assign the value of the first element in the linked list

    // iterate through linked list until NULL pointer (end of the list)
    while (temp != NULL)
    {
        int match = strcasecmp(temp->wrd, wd);      // compare string from file with content of the node in linked list

        // compare strings from the file and dictionary, if the words match, return true
        if (match == 0)
        {
            return true;        // word from file matches that from the linked list
        }
        temp = temp->next;      // traverse through the linked list
    }

    // end of function, word not found in dictionary, return false
    return false;
}


// loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declare variables
    char word[LENGTH + 1];                                      // string pointer, will store word uploaded from file
    hashtable = (node_t*) calloc(BUCKETS, sizeof(node_t));      // allocate memory for hashtable (use calloc for array)

    FILE *dict_file = fopen(dictionary, "r");                   // open input file
    if (dict_file == NULL)                                      // check if input file opened succesfully
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
    }

    // read words from dictionary file and save in the linked list
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        // determine which bucket to go to using hash function
        int key = hash(word);

        // create new node and confirm the memory allocated succesfully
        node_t *new_node = malloc(sizeof(node_t));
        if (new_node == NULL)
        {
            unload();
            return false;       // if memory not allocated succesfully, unload and return false
        }

        // check if the head pointer is pointing to NULL, if so, this means the bucket is still empty and
        // this node is the first node, so needs to point at NULL
        if ((hashtable+key)->next == NULL)
        {
            new_node->next = NULL;
        }
        // if head pointer isn't NULL, the bucket already contains a node, then our node isn't the first one
        // in the bucket and needs linking in
        else
        {
            new_node->next = (hashtable+key)->next;     // point new node at the current first node in the bucket
        }
        strcpy(new_node->wrd, word);                    // copy 'word' into the new node
        (hashtable+key)->next = new_node;               // point head pointer at new node
    }

    // success, close file, return true
    fclose(dict_file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // declare variable
    int count = 0;

    // iterate through the hashtable and count all items
    for (int bucket = 0; bucket < BUCKETS; bucket++)        // iterating through buckets
    {
        node_t *temp2 = (hashtable+bucket)->next;           // create temporary node and point it at the current first node

        // check if temp node is NULL, therefore bucket is empty
        if (temp2 != NULL)
        {
            while (temp2 != NULL)                           // iterating through linked list inside bucket
            {
                count++;
                temp2 = temp2->next;                        // point temp node at the next node in the list
            }
        }
    }

    // success, end of function, return count
    return count;
}


// unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate through all buckets in the hashtable
    for (int bucket = 0; bucket < BUCKETS; bucket++)
    {
        // iterate through each node in the linked list
        while ((hashtable+bucket)->next != NULL)
        {
            node_t *temp1 = (hashtable+bucket)->next;   // point temp node at the first node in the bucket
                                                        // (at whatever the head node is pointing at)
            (hashtable+bucket)->next = temp1->next;     // point the head node at the second node in the bucket
                                                        // (at the address stored as 'next' in the first node [not the head node])
            free(temp1);                                // free the first node in the bucket [not the head node]
                                                        // the second node has now become the first
        }
    }

    // free the hashtable
    free(hashtable);

    // success, return true
    return true;
}

