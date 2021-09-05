/*
* Author: Sander Selnes Toresen
* Trie data structure for storing words
* supports lowercase letters from a-z.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "trie.h"
#include "list.h"

typedef struct node node_t;

#define CHARACTERS 26 //NR. of characters a-z, where a = 0, z = 25

struct trie
{
    int words;
    node_t *head;
};

/*
* nodes storing words and link to children
*/
struct node
{
    node_t *array[CHARACTERS];
    char *word;
    bool isWord;
};

/*
* Create node
*/
node_t *node_create(char *word, bool isWord)
{
    node_t *node = calloc(1, sizeof(node_t));
    if (node == NULL)
    {
        printf("ERROR creating node\n");
        return NULL;
    }

    node->word = malloc(strlen(word) * sizeof(char));
    if (node->word == NULL)
    {
        return NULL;
    }
    strcpy(node->word, word);
    node->isWord = isWord;
    return node;
}

trie_t *trie_create()
{
    trie_t *trie = malloc(sizeof(trie_t));
    if (trie == NULL)
        return NULL;

    trie->head = node_create("", false);
    trie->words = 0;

    return trie;
}

/*
* Reccursive function, destroy all nodes under the given node
*/
static void __destroy_nodes(node_t *n)
{
    if (!n)
        return;

    for (int i = 0; i < CHARACTERS; i++)
    {
        if (n->array[i] != NULL)
        {
            __destroy_nodes(n->array[i]);
        }
    }

    free(n->word);
    free(n);
}

void trie_destroy(trie_t *trie)
{
    __destroy_nodes(trie->head);
    free(trie);
}

/*
* transform char (a-z) to
* corresponding index
*/
int __char_to_index(char c)
{
    if ((int)c > 122 || (int)c < 97) //check char is a-z
    {
        printf("Invalid char: %c\n", c);
        return -1;
    }
    return (int)c - 97; //return index
}

/*
* Traverse tree, both for adding and looking up words.
* Arguments:
* node_t *node    : current leaf node
* char *word      : word we're traversing to
* char *c         : only used when adding word! The next node after word.
* bool lastLetter : only used when adding word! If set node is marked as a complete word.
* bool adding     : Set if adding word, not set if looking up word.
*/
static node_t *__traverse_tree(node_t *node, char *word, char c, bool lastLetter, bool adding)
{
    int index = __char_to_index(c);

    if (index < 0 || index >= CHARACTERS)
    { //raise error if character is not between a-z
        printf("FATAL ERROR, invalid word '%s'\n", word);
        return NULL;
    }

    if (!node)
    {
        return NULL;
    }

    //traverse to child node
    node_t *next = node->array[index];
    if (adding)
    { //create node if it don't exist
        if (next == NULL)
        {
            bool isWord = false;
            next = node_create(word, isWord);
            node->array[index] = next;
        }

        //if last letter, word complete
        if (lastLetter)
            next->isWord = true;
    }
    return next;
}

int trie_add_word(trie_t *trie, char *word)
{
    node_t *n = trie->head;
    bool lastLetter = false;

    for (int i = 0; i < strlen(word); i++) //add word by traversing the tree
    {
        //slice word for node
        int slice_len = i + 1;
        char sliced_word[slice_len];

        //copy slice
        memcpy(sliced_word, word, sizeof(char) * slice_len);
        sliced_word[slice_len] = '\0';

        if (word[i + 1] == '\0') //set end of word flag
            lastLetter = true;

        if ((int)word[i] != 0) // assert word is valid
            n = __traverse_tree(n, sliced_word, word[i], lastLetter, true);
    }
}

/*
* find all valid words in node and child nodes
* all words are added to the given list
*/
void __find_words(node_t *n, list_t *suggestions)
{
    if (!n)
        return;

    if (n->isWord) //if valid word, add it
    {
        //allocate space copy word and store it in list
        char *word = malloc(strlen(n->word) * sizeof(char));
        stpcpy(word, n->word);
        list_push(suggestions, word);
    }

    // look for words in all child nodes
    for (int i = 0; i < CHARACTERS; i++)
    {
        if (n->array[i])
        {
            __find_words(n->array[i], suggestions);
        }
    }
}

void *trie_get_suggestions(trie_t *trie, char *str)
{
    list_t *suggestions = list_create();

    //return if invalid characters are used
    for (int i = 0; i < strlen(str); i++)
    {
        if (__char_to_index(str[i]) == -1)
        {
            printf("returning null\n");
            return NULL;
        }
    }

    //traverse tree untill correct node
    node_t *curr = trie->head;

    //traverse untill curr corresponds to last letter in str
    for (int i = 0; i < strlen(str); i++)
    {
        int index = __char_to_index(str[i]);
        curr = __traverse_tree(curr, "", str[i], false, false);

        if (!curr) // no words matching search
            return suggestions;
    }

    //at correct node, scan all child nodes for valid words
    __find_words(curr, suggestions);

    return suggestions;
}