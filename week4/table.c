#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 45
#define ALL_BUCKETS 25

// define global data structures and variables
typedef struct node {
    char wrd[LENGTH + 1];                       // will hold words loaded from dictionary file
    struct node * next;                         // will hold pointer to the next item in the list
} node_t;


int hash(int c);


int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // declare variables
    node_t *hashtable;                              // create hashtable
    char word[LENGTH + 1];
    memset(word, '\0', LENGTH + 1);
    char *dictionary = argv[1];
    hashtable = (node_t*) calloc(ALL_BUCKETS, sizeof(node_t));

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
        node_t *temp = malloc(sizeof(node_t));
        if ((hashtable+key)->next == NULL)
        {
            temp->next = NULL;
        }
        else
        {
            temp->next = (hashtable+key)->next;
        }
        strcpy(temp->wrd, word);
        (hashtable+key)->next = temp;
        memset(word, '\0', LENGTH + 1);
    }

    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        while ((hashtable+bucket)->next != NULL)
        {
            node_t *temp1 = (hashtable+bucket)->next;
            free((hashtable+bucket)->next);
            (hashtable+bucket)->next = temp1->next;
            //free(temp1);
        }
        //free(hashtable+bucket);
    }
    //free(hashtable);

    // success, close file, return true
    fclose(dict_file);
    return 0;
}



int hash(int c)
{
    if (c < 97)
        c += 32;

    return c -= 97;
}