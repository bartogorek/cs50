// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


// HELPER functions
// hash function
int hash(int c)
{
    if (c < 97)
        c += 32;

    return c -= 97;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // declare word string;
    int len = strlen(word);
    char wrd[len];
    strcpy(wrd, word);

    // ensure all characters are lower case
    for (int z = 0; z < strlen(word); z++)
    {
        if (isalpha(wrd[z]) && isupper(wrd[z]))
            wrd[z] = tolower(wrd[z]);
    }

    // add a check for node creator
    //if (!temp)
    //    return false;

    int key = hash(wrd[0]);                     // hash the input word to establish key (bucket number)
    node_t *temp = hashtable[key].next;         // assign the value of the first element in the linked list

    // iterate through linked list until NULL pointer (end of the list)
    while (temp != NULL)
    {
        // compare string from the file and dictionary, if the words match, return true
        if (strcmp(temp->wrd, wrd) == 0)
        {
            return true;
        }
        temp = temp->next;
    }

    // free memory
    free(temp);

    // end of function, word not found in dictionary return false
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declare variables
    //char *word = malloc((sizeof(char) * LENGTH) + 1);   // allocate memory to store 'word', max length as defined in LENGTH + 1
    char word[LENGTH + 1];
    hashtable = calloc(ALL_BUCKETS, sizeof(node_t));
    //hashtable = malloc(sizeof(node_t) * ALL_BUCKETS);

    FILE *dict_file = fopen(dictionary, "r");           // open input file
    if (dict_file == NULL)                              // check if input file opened succesfully
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
    }

    // read words from dictionary file and save in the linked list
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        // determine which bucket to go to using hash function
        int key = hash(word[0]);

        // create new node and append to the appropriate bucket
        node_t *temp = malloc(sizeof(node_t));      // create new node
        // add a check for node creator

        if (hashtable[key].next == NULL)
        {
            temp->next = NULL;
        }
        else
        {
            temp->next = hashtable[key].next;       // assign it the value of the first element in the list
                                                    // in the hash table
        }
        strcpy(temp->wrd, word);                    // copy 'word' from the dictionary into the node
        hashtable[key].next = temp;                 // insert newly created node into the first slot in the hash table
    }

    // success, close file, return true
    //free(word);
    fclose(dict_file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    // iterate over hashtable, count all items
    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        node_t *temp2 = hashtable[bucket].next;

        if (temp2 != NULL)
        {
            while (temp2 != NULL)
            {
                count++;
                temp2 = temp2->next;
            }
            //free(temp2);
        }
        free(temp2);
    }
    //free(temp2);
    return count;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // free all nodes from every bucket
    //node_t *temp1 = malloc(sizeof(node_t));      // temporary storage for traversing

    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        if (hashtable[bucket].next != NULL)
        {
            while (hashtable[bucket].next != NULL)
            {
                node_t *temp1 = hashtable[bucket].next;
                free(hashtable[bucket].next);
                //free(hashtable[bucket]);

                // program was falling over when assigning temp-> when it was NULL, so this avoids it - FIX ??
                if (temp1->next != NULL)
                    hashtable[bucket].next = temp1->next;
                else
                    hashtable[bucket].next = NULL;        // if we're on the last node, set temp to NULL to break out of loop

                temp1 = NULL;
                free(temp1);
            }
        }
        //free(temp1);
    }
    free(hashtable);

    return true;
}

