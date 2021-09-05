/*
* Author: Sander Selnes Toresen
* Simple array based stack-like list
* works by pushing and popping
*/
#ifndef list_H
#define list_H

/*
 * Define struct
 */
typedef struct list list_t;

/*
 * Returns the new list.
 */
list_t *list_create();

/*
 * Destroy list, removes the list, not the stored elements
 */
void list_destroy(list_t *list);

/*
 * Returns the current length of the given list.
 */
int list_length(list_t *list);

/*
 * Push element at the end of the list
 */
int list_push(list_t *list, void *elem);

/*
* Pop the last element in the list
*/
void *list_poplast(list_t *list);

#endif
