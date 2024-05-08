## PO2 - Linear Search
### Kate Morgan
### Description:

Using Json and Getch, this program performs linear search to create a suggestive search based on the user's character input. The user will be asked to enter characters of the word they are searching for. This program will find matches to the users input, that are words begining with the string inpiuted by the user. The program will print out the total matches found, and will print out the top 10 results.
### Files

|   #   | File             | Description                                        |
| :---: | ---------------- | -------------------------------------------------- |
|   1   | [main.cpp](P01/main.cpp)       | Main file for running the program|
| 2 | [Output1] (PO2/Output1) | example output 1| 
| 3 | [Output2] (PO2/Output2) | example output 2| 
| 4 | [Output3] (PO2/Output3) | example output 3| 
| 5 | [Output4] (PO2/Output4) | example output 4| 


### Instructions
Use main. cpp and all .hpp required to run the
program expects no parameters to be placed on the command line when you run the program
The input should consist of characters
When a single word is found, hit the enter key to terminate the program
To terminate without finding a word, enter 'Z'

### Requirements
- Write a program that will combine the two files: `main.cpp` and `loadJsonEx.cpp` so that `main.cpp` uses the dictionary to look for partial matches in. 
- Time how long it takes to load the data into the json object initially. 
- After your dictionary is loaded, we are going to perform "autosuggestions" when a user types characters at the console.
- Suggestions will start after 1 character is typed, however only the top 10 suggestions will be printed along with the total number of matching words (example output below).
- Matching suggestions will ONLY be words that match the substring starting from position zero. For example: `cat` would match `cat`, `caterpillar`, and `cattle`. But **NOT** `wildcat`.
- As typing, the time it takes to find suggestions will be displayed in seconds. Like: `0.0000554310000000019` seconds.
- In addition I have included a file to help color text. Docs are here: https://termcolor.readthedocs.io/ but I included some examples in [main.cpp](main.cpp).