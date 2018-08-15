

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
    //hashtable = calloc(ALL_BUCKETS, sizeof(node_t));
    hashtable = (node_t*) calloc (ALL_BUCKETS, sizeof(node_t));
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
        // add a check for node creator

        if ((hashtable+key)->wrd[0] == 0)
        {
            strcpy((hashtable+key)->wrd, word);
            (hashtable+key)->next = NULL;
        }
        else
        {
            //node_t *temp = malloc(sizeof(node_t));      // create new node
            //temp->next = (hashtable+key)->next;
            node_t *temp = (hashtable+key);
            //strcpy(temp->wrd,(hashtable+key)->wrd);         // assign it the value of the first element in the list in the hash table
            strcpy((hashtable+key)->wrd, word);             // copy 'word' from the dictionary into the node
            (hashtable+key)->next = temp;                   // insert newly created node into the first slot in the hash table
            node_t *boom = (hashtable+key)->next;
            printf("%s\n", boom->wrd);
        }
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
        node_t *temp = (hashtable+bucket);              // assign the value of the first element in the linked list

        // iterate through linked list until NULL pointer (end of the list)

        if ((hashtable+bucket)->wrd[0] != 0)
        {
            while (temp != NULL)
            {
                printf("%s\n", temp->wrd);
                temp = temp->next;
            }
            free(temp);
        }
    }

    // success, return true
    return true;
}


bool unload(void)
{
    // free all nodes from every bucket

    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        if ((hashtable+bucket)->wrd[0] != 0)
        {
            printf("Freeing bucket: %i\n", bucket);

            while ((hashtable+bucket)->next != NULL)
            {
                node_t *temp1 = (hashtable+bucket)->next;

                //free((hashtable+bucket)->wrd);
                //free((node_t *) (hashtable+bucket));

                (hashtable+bucket)->next = temp1->next;
                strcpy((hashtable+bucket)->wrd, temp1->wrd);

                free(temp1);
            }
        }
    }
    /*
    for (int q = 0; q < ALL_BUCKETS; q++)
    {
        free((node_t *) (hashtable+q));
    }*/

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
