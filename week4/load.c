// test program implementing 'load' function for pset5 of CS50



// include libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// define constant values
#define BUCKETS 25                      // number of buckets in the hashtable
#define LENGTH 45                       // maximum word length

// define global data structures and variables
typedef struct node {
    char wrd[LENGTH + 1];                       // will hold words loaded from dictionary file
    struct node * next;                         // will hold pointer to the next item in the list
} node_t;
struct node *hashtable;                              // create hashtable as global var


// prototype functions
bool load(const char *dictionary);              // loads dictionary into memory
int hash(int c);                                // hash function



// main program
int main(int argc, char* argv[])
{
    // ensure correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage : ./load <dictionary>\n");
        return 1;
    }

    // declare data structures
    char *infile = argv[1];                         // remember input file
    hashtable = malloc(sizeof(node_t) * BUCKETS);   // allocate memory for hashtable

    for (int z = 0; z < BUCKETS; z++)               // fill all head nodes in hashtable with '\0'
        hashtable[z].wrd[0] = '\0';

    // load dictionary into a data structure (calling function 'load')
    bool loaded = load(infile);


    // test print content of linked list
    printf("Test printing:\n");

    //for (int i = 1; i < 2; i++)
    //{
        int w = 0;
        node_t *current = malloc(sizeof(size_t));
        current = &hashtable[1];       // temporary node for traversing
        while (current != NULL && w < 10)
        {
            //if (hashtable[i].wrd[0] != '\0')
            printf("%s\n", current->wrd);
            current = current->next;
            w++;
        }
    //}


/*
    printf("testing : \n");
    node_t *current = malloc(sizeof(node_t));
    current = &hashtable[1];
    printf("%s\n", current->wrd);
    current = current->next;
    printf("%s\n", current->wrd);
     printf("%s\n", current->wrd);
    current = current->next;
    printf("%s\n", current->wrd);
    current = current->next;
    printf("%s\n", current->wrd);
    current = current->next;
*/

    //free(current);


    // print all items from the data struct
    if (loaded)
        printf("success\n");

    return 0;
}



// HELPER functions
// function loading dictionary from file into data struct
bool load(const char *dictionary)
{
    // declare variables
    char *word = malloc((sizeof(char) * LENGTH) + 1);   // allocate memory for to store 'word', max length as defined in LENGTH

    // open file and confirm it's valid
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
        return false;
    }
    else
    {
        printf("loading dictionary\n");
    }

    // iterate over characters in the dictionary file
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        int key = hash(word[0]);

        if (hashtable[key].wrd[0] == '\0')
        {
            node_t *item = malloc(sizeof(node_t));
            // add a line to check if new node created successfully
            strcpy(item->wrd, word);
            item->next = NULL;
            hashtable[key] = *item;                             // copy content of word inside the node 'head', as pointed
            printf("inside node: %s\n", hashtable[key].wrd);    // test print
        }
        else
        {
            // push element to the beginning of the linked list
            node_t *item2 = malloc(sizeof(node_t));                  // create new node
            // add a line to check if new node created successfully
            item2->next = NULL;
            strcpy(item2->wrd, word);                                // copy 'word' into 'wrd' inside the new node
            item2->next = &hashtable[key];                                 // point new node's pointer to the current 'head'
            hashtable[key] = *item2;                                 // new node becomes the new 'head'
            printf("inside node: %s\n", hashtable[key].wrd);            // test printing
        }
    }

    // success, free memory, close file, return true
    free(word);
    printf("closing file once operations complete\n");
    fclose(dict_file);
    return true;
}

// hash function
int hash(int c)
{
    if (c < 97)
        c += 32;

    c = c - 97;
    return c;
}
