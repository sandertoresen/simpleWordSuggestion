/*
* Author: Sander Selnes Toresen
* Trie data structure for storing words
* supports lowercase letters from a-z.
*/
#ifndef trie_H
#define trie_H

/*
 * Define structure
 */
typedef struct trie trie_t;

/*
 * Create and return trie.
 */
trie_t *trie_create();

/*
 * Destroy trie tree.
 */
void trie_destroy(trie_t *trie);

/*
 * add word to the trie
 */
int trie_add_word(trie_t *trie, char *word);

/*
* Get list of suggestions based on str.
* Ect. if str = "ba"
* list of suggestions such as: bad, barn, banana
* would be returned, if added to the trie.
*/
void *trie_get_suggestions(trie_t *trie, char *str);

#endif
