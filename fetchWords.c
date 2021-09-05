/*
* Author: Sander Selnes Toresen
* Function for fetching the data from wordlist.txt
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

/*
* Takes file and copies each line into list
*/
void *fetch_data(char *src)
{
    FILE *fp = fopen(src, "r");
    if (!fp)
    {
        printf("error opening file\n");
        return NULL;
    }

    list_t *words = list_create();

    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_size;
    int lines = 0;

    line_size = getline(&buffer,
                        &buffer_size, fp); //get first line

    //add each line/word to list
    while (line_size >= 0)
    {
        lines++;
        buffer[strlen(buffer) - 1] = '\0'; // remove newline
        char *word = malloc(strlen(buffer) * sizeof(char));
        stpcpy(word, buffer);
        list_push(words, word);
        line_size = getline(&buffer, &buffer_size, fp);
    }
    free(buffer);
    fclose(fp);

    return words;
}