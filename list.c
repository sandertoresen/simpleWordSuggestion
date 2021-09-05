/*
* Author: Sander Selnes Toresen
* Simple array based stack-like list
* works by pushing and popping
*/
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct list;

static int ARRAY_SIZE = 64; //array start size

struct list
{
    void **array;
    int capacity; //current max elements
    int count;    //nr. of elements
};

list_t *list_create()
{
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;

    list->array = (void *)malloc(ARRAY_SIZE * sizeof(void *));
    if(!list->array)
        return NULL;
    list->capacity = ARRAY_SIZE;
    list->count = 0;

    return list;
}

/*
* Create new extended array, transfer pointers and delete old array
*/
static void __extend_array(list_t *list)
{
    if (list == NULL)
    {
        return;
    }

    void **prev = list->array;
    list->capacity *= 2; //double capacity

    //create new extended array
    list->array = (void *)malloc(list->capacity * sizeof(void *));
    if (!list->array){
        printf("ERROR extending array\n");
        return;
    }
        
    //transfer elements
    for (int i = 0; i < list->count; i++)
    {
        list->array[i] = prev[i];
    }

    free(prev); //free old elements
}

int list_push(list_t *list, void *elem)
{
    if (list == NULL || elem == NULL)
    {
        return -1;
    }

    //extend list if full
    if (list->capacity == list->count)
    {
        __extend_array(list);
    }

    list->array[list->count++] = elem; //add element to list and increment the list
    return 1;
}

void *list_poplast(list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (list->count == 0)
    {
        return NULL;
    }

    void *elem = list->array[list->count-- - 1]; // fetch element and decrease count

    return elem;
}

void list_destroy(list_t *list)
{
    free(list->array);
    free(list);
}

int list_length(list_t *list)
{
    return list->count;
}
