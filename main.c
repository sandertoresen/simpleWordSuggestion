/*
* Author: Sander Selnes Toresen
* Gives a simple interface for testing 
* trie data structure
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "trie.h"
#include "fetchWords.h"

// srand(time(0)); // enable random numbers
// // rand_num = rand();

/*
* Fill trie with data from wordlist.txt
* wordlist.txt should be generated with
* formatText.py
*/
void fill_trie(trie_t *trie)
{
    list_t *words = fetch_data("wordlist.txt");
    char *word = list_poplast(words);
    while (word)
    {
        trie_add_word(trie, word);
        free(word);
        word = list_poplast(words);
    }
    printf("Trie filled!\n");
}

/*
* assert string only contains a-z
*/
int assert_valid(char *str)
{
    if(str[0] == '\0')
        return -1;

    for (int i = 0; i < strlen(str); i++)
    {
        if ((int)str[i] > 122 || (int)str[i] < 97)
        {
            return -1;
        }
    }
    return 1;
}

int main()
{
    printf("\n----------Author: Sander Selnes Toresen----------\n\n");

    trie_t *trie = trie_create();
    fill_trie(trie);

    while (1)
    {
        char word[20];
        printf("type part of a word:");
        scanf("%30s", word);
        if (assert_valid(word) != 1)
        {
            printf("OBS: string not valid..\n");
        }
        else
        {
            list_t *suggestions = trie_get_suggestions(trie, word);
            printf("Words starting with \"%s\": \n", word);

            while (list_length(suggestions))
            {
                char *res = list_poplast(suggestions);
                printf("%s", res);

                if (list_length(suggestions))
                {
                    printf(", ");
                }
            }
            if(list_length(suggestions))
                printf(".\n\n");
            else
                printf("no matching words.\n\n\n");

            list_destroy(suggestions);
        }
    }
}