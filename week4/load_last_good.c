// test program implementing 'load' function for pset5 of CS50



// include libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// define constant values
#define LENGTH 45                       // maximum word length

// define global data structures
typedef struct node {
    char wrd[LENGTH + 1];                       // will hold words loaded from dictionary file
    struct node * next;                         // will hold pointer to the next item in the list
} node_t;

// prototype functions
bool load(const char *dictionary, node_t ** head);      // loads dictionary into memory
void push(node_t ** head, char *word);                  // adds item to the beginning of linked list



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
    node_t * head = NULL;                           // create an instance of node_t
    head = malloc(sizeof(node_t));                  // allocate memory for 'head'

    // confirm succesful
    if (head == NULL)
        return 1;

    // load dictionary into a data structure (calling function 'load')
    bool loaded = load(infile, &head);

    // test print content of linked list
    node_t * current = head;       // temporary node for traversing
    printf("Test printing:\n");
    while (current != NULL)
    {
        printf("%s\n", current->wrd);
        current = current->next;
    }

    // free all memory used to store dictionary
    node_t * temp = head;           // temporary node for traversing
    while (temp != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }

    // print all items from the data struct
    if (loaded)
        printf("success\n");

    return 0;
}



// HELPER functions
// function loading dictionary from file into data struct
bool load(const char *dictionary, node_t ** head)
{
    // declare variables
    char *word = malloc(sizeof(char) * LENGTH);     // allocate memory for to store 'word', max length as defined in LENGTH
    int count = 0;                                  // count characters in each word
    int wrd_count = 0;                              // count words

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
    for (int c = fgetc(dict_file); c != EOF; c = fgetc(dict_file))
    {
        if (c != '\n')
        {
            word[count] = c;        // assign character to 'word'
            count++;                // increment counter
        }
        else
        {
            printf("%s\n", word);

            if (wrd_count == 0)
            {
                strcpy((*head)->wrd, word);                 // copy content of word inside the node 'head', as pointed
                printf("inside node: %s\n", (*head)->wrd);
                (*head)->next = NULL;                       // set the value of next to NULL, 'head' is the last item of the list
            }
            else
            {
                // push element to the beginning of the linked list
                push(head, word);
            }

            memset(word, '\0', LENGTH);                     // clear content of 'word', ready for next word
            count = 0;                                      // reset character counter
            wrd_count++;                                    // increment word counter
        }
    }

    push(head, word);       // call push function once again to assign last word

    // success, free memory, close file, return true
    free(word);
    printf("closing file once operations complete\n");
    fclose(dict_file);
    return true;
}

// push function adds item to the beginning of the linked list
void push(node_t ** head, char *word)
{
    node_t * new_node;                          // create new node
    new_node = malloc(sizeof(node_t));          // allocate memory
    strcpy(new_node->wrd, word);                // copy 'word' into 'wrd' inside the new node
    new_node->next = *head;                     // point new node's pointer to the current 'head'
    *head = new_node;                           // new node becomes the new 'head'
    printf("inside node: %s\n", (*head)->wrd);  // test printing
}