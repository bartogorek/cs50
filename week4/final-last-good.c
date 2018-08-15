

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// define constant values
#define LENGTH 45
#define ALL_BUCKETS 25

// define global data structures and variables
typedef struct node {
    char wrd[LENGTH + 1];                       // will hold words loaded from dictionary file
    struct node * next;                         // will hold pointer to the next item in the list
} node_t;
node_t *hashtable;
//struct node *hashtable;

// prototype helper functions
int hash(int c);
bool load(const char *dictionary);
bool check(void);
bool unload(void);
unsigned int size(void);


// main program
int main(int argc, char* argv[])
{
    // ensure correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage : ./load <dictionary>\n");
        return 1;
    }

    // declare data structures and variables
    //hashtable = malloc(sizeof(node_t) * ALL_BUCKETS);   // allocate memory for hashtable
    hashtable = calloc(ALL_BUCKETS, sizeof(node_t));
    //hashtable = (node_t*) malloc (ALL_BUCKETS * sizeof(node_t));
    char *infile = argv[1];                             // remember input file

    // load dictionary into memory
    bool loaded = load(infile);
    if (!loaded)
        printf("Failed loading");

    // print the content of all buckets
    bool checked = check();
    if (!checked)
        printf("Failed check");

    // count words in the hashtable
    int result = size();
    printf("%i\n", result);

    // print the content of all buckets
    bool unloaded = unload();
    if (!unloaded)
        printf("Unload failed");




    // success, return 0
    return 0;
}



// HELPER functions

// hash function
int hash(int c)
{
    if (c < 97)
        c += 32;

    return c -= 97;
}


// load function
bool load(const char *dictionary)
{
    // declare variables
    char *word = malloc((sizeof(char) * LENGTH) + 1);   // allocate memory to store 'word', max length as defined in LENGTH + 1

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
            temp->next = hashtable[key].next;           // assign it the value of the first element in the list
                                                        // in the hash table
        }
        strcpy(temp->wrd, word);                    // copy 'word' from the dictionary into the node
        hashtable[key].next = temp;                 // insert newly created node into the first slot in the hash table
    }

    // success, close file, return true
    free(word);
    fclose(dict_file);
    return true;
}


// currently printing function, prints all buckets
bool check(void)
{
    // temporary storage for traversing
    //node_t *temp = malloc(sizeof(node_t));      // create new node

    // iterate through each bucket
    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        printf("Printing bucket: %i\n", bucket);

        // add a check for node creator
        node_t *temp = hashtable[bucket].next;              // assign the value of the first element in the linked list

        // iterate through linked list until NULL pointer (end of the list)
        while (temp != NULL)
        {
            printf("%s\n", temp->wrd);
            temp = temp->next;
        }
        free(temp);
    }

    // success, return true
    return true;
}


bool unload(void)
{
    // free all nodes from every bucket
    node_t *temp1 = malloc(sizeof(node_t));      // temporary storage for traversing
    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        if (hashtable[bucket].next != NULL)
        {
            printf("Freeing bucket: %i\n", bucket);

            while (hashtable[bucket].next != NULL)
            {
                temp1 = hashtable[bucket].next;
                free(hashtable[bucket].next);

                // program was falling over when assigning temp-> when it was NULL, so this avoids it - FIX ??
                if (temp1->next != NULL)
                {
                    hashtable[bucket].next = temp1->next;
                }
                else
                    hashtable[bucket].next = NULL;        // if we're on the last node, set temp to NULL to break out of loop

                temp1 = NULL;
                free(temp1);
            }
        }
        free(temp1);
    }
    free(hashtable);

    return true;
}


unsigned int size(void)
{
    int count = 0;
    //node_t *temp2 = malloc(sizeof(node_t));

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
