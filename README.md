Simple word suggestion program.

Requirements:
python, c

Files:
beeMovieScript.txt : test data for program
formatText.py      : takes a text, removes special characters and turn uppercase letters into lowercase and creates "wordlist.txt"
fetchwords(.c)(.h) : function for writing words from "wordlist.txt" into a linked list.
list(.c)(.h)       : simple array linked list with pop and push like functionallity
trie(.c)(.h)       : trie tree structure for storing words and fetching them.
main.c             : simple interface for testing the trie.
---------------------------------------------------------------------------------------------------------------------------------------
Run:
python3 formatText.py path/to/file.txt -> creates "wordlist.txt"
gcc -o app fetchwords.c list.c trie.c main.c -> creates ./app
./app -> gives simple interface for word suggestions from wordlist.txt

Example:
By storing "foo" and "fo" in trie a tree structure looking like this would be generated:

head->[] [] [] [] [] [f] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] 
                     \/
      [] [] [] [] [] [] [] [] [] [] [] [] [] [] [o] [] [] [] [] [] [] [] [] []
                                                \/
      [] [] [] [] [] [] [] [] [] [] [] [] [] [] [o] [] [] [] [] [] [] [] [] []

Searching for suggestions with for words starting with "f" would return "fo" and "foo" in a list.

