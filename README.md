# Simple word suggestion program.
Author: Sander Selnes Toresen

## Requirements:
python, c

## Files
| File                   | Description |
| :-----------------------|:-------------------------------------------------------------------------------------------------------------|
| **beeMovieScript.txt** | test data for program
| **formatText.py**      | takes a text, removes special characters and turn uppercase letters into lowercase and creates "wordlist.txt"
| **fetchwords(.c)(.h)** | function for writing words from "wordlist.txt" into a linked list.
| **list(.c)(.h)**       | simple array linked list with pop and push like functionallity
| **trie(.c)(.h)**       | trie tree structure for storing words and fetching them.
| **main.c**             | simple interface for testing the trie.
---

## Run:
**python3 formatText.py path/to/file.txt** -> creates "wordlist.txt"</br>
**gcc -o app fetchwords.c list.c trie.c main.c** -> creates ./app</br>
**./app** -> gives simple interface for word suggestions from wordlist.txt

## Example:
By storing "foo" and "fo";
Searching for suggestions with for words starting with "f" would return "fo" and "foo" in a list.

