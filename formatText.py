""" Author: Sander Selnes Toresen
Simple spagetti script to fetch all words from a file
and formating a wordlist.txt with only lowercase words from
a-z. 
USAGE: python3 formatedText.py path/to/text/file.txt
"""
from sys import argv
from os.path import exists

if __name__ == "__main__":
    if len(argv) != 2:
        print("usage: python3 formatText.py path/to/text/file.txt")
        exit()

    if not exists(argv[1]):
        print(f"'{argv[1]}' is an invalid path")
        exit()

    f = open(str(argv[1]), "r")  # open source file

    words = []
    for line in f:  # get all words from file
        for word in line.split():
            words.append(word)
    f.close()

    tmp = []
    # filter words, remove special characters and uppercase
    for i in range(len(words)):
        w = ""
        for c in words[i]:
            num_val = ord(c)
            if num_val >= 65 and num_val <= 90:  # change upper to lowercase
                w += chr(num_val + 32)

            elif num_val >= 97 and num_val <= 122:  # add lowercase
                w += c

        if w not in tmp and w != "":  # add word if not dupe or empty
            tmp.append(w)

    words = tmp

    # write words to "wordlist.txt"
    formated = open("wordlist.txt", "w")

    for word in words:
        formated.write(word + '\n')

    formated.close()
