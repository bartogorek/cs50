

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// define global data structures and variables
typedef struct node {
    char wrd[45];                       // will hold words loaded from dictionary file
    struct node * next;                         // will hold pointer to the next item in the list
} node_t;
node_t *hashtable;

#define STRLEN 10
#define BUCKETS 1

bool load(char);              // loads dictionary into memory

int main()
{
    char *str1 = malloc(sizeof(char) * STRLEN);
    char *str2 = malloc(sizeof(char) * STRLEN);
    char *str3 = malloc(sizeof(char) * STRLEN);
    char *str4 = malloc(sizeof(char) * STRLEN);

    hashtable = malloc(sizeof(node_t) * BUCKETS);

    str1 = "bobo";
    str2 = "momo";
    str3 = "jojo";
    str4 = "sisi";

    int key = 0;

    node_t *one = malloc(sizeof(node_t));
    one->next = NULL;
    strcpy(one->wrd, str1);

    node_t *two = malloc(sizeof(node_t));
    two->next = one;
    strcpy(two->wrd, str2);

    node_t *three = malloc(sizeof(node_t));
    three->next = two;
    strcpy(three->wrd, str3);

    node_t *four = malloc(sizeof(node_t));
    four->next = three;
    strcpy(four->wrd, str4);

    hashtable[key] = *four;

    node_t *test = malloc(sizeof(node_t));
    test = &hashtable[key];
    while (test != NULL)
    {
        printf("%s\n", test->wrd);
        test = test->next;
    }

    free(one);
    free(two);
    free(three);
    free(four);
    free(test);
    free(hashtable);

    return 0;
}