

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
    char *word = malloc((sizeof(char) * LENGTH) + 1);   // allocate memory to store 'word', max length as defined in LENGTH + 1
    hashtable = malloc(sizeof(node_t) * ALL_BUCKETS);

    // remember input file, open and confirm it's valid
    char *infile = argv[1];                     // remember input file
    FILE *dict_file = fopen(infile, "r");       // open input file
    if (dict_file == NULL)                      // check if input file opened succesfully
    {
        fprintf(stderr, "Could not open %s\n", infile);
    }

    // read words from dictionary file and save in the linked list
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        // deteermine which bucket to go to using hash function
        int key = hash(word[0]);

        // check if bucket is empty and if so create the first node
        /*if (hashtable[key].next == NULL)
        {
            node_t *one = malloc(sizeof(node_t));
            one->next = NULL;
            strcpy(one->wrd, word);
            hashtable[key].next = one;
            //free(one);
        }
        else if (hashtable[key].next != NULL)
        {*/
            node_t *temp = malloc(sizeof(node_t));
            strcpy(temp->wrd, word);
            temp->next = hashtable[key].next;
            hashtable[key].next = temp;
        //}
    }


    // print the content of linked list for each bucket
    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {
        printf("Printing bucket: %i\n", bucket);

        node_t *temp = malloc(sizeof(node_t));      // temporary storage for traversing
        temp = hashtable[bucket].next;

        while (temp != NULL)
        {
            printf("%s\n", temp->wrd);
            temp = temp->next;
        }
        free(temp);
    }
/*
    // free all nodes from every bucket
    for (int bucket = 0; bucket < ALL_BUCKETS; bucket++)
    {

        if (hashtable[bucket].next != NULL)
        {
            printf("Freeing bucket: %i\n", bucket);

            node_t *temp = malloc(sizeof(node_t));      // temporary storage for traversing

            while (temp != NULL)
            {
                temp = &hashtable[bucket];
                hashtable[bucket] = &hashtable[bucket].next;
                free(hashtable[bucket]);
            }*/
        /*
          1. tmp = head;
          2. head = head->next;
          3. free(tmp);
        */

        //}
    //}

    // success, free memory, close files, return 0
    fclose(dict_file);
    free(word);
    free(hashtable);
    //free(one);

    return 0;
}


// HELPER functions
// hash function
int hash(int c)
{
    if (c < 97)
        c += 32;

    c = c - 97;

    return c;
}