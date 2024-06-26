 /*
 *  Author:           Kate Morgan
 *  Title:            Linear Search
 *  Course:           CMPS 3013
 *  Semester:         Spring 2024

 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it
 * lets you decide what to do based on what character you are pressing.
 *
 * You can test which characters are being pressed using their ascii values.
 *
 * An ascii table here should be helpful
 *      http://www.asciitable.com/
 *
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between
 *                            the two (in this context).
 *
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches.
 *
 * https://repl.it/@rugbyprof/getchexample#main.cpp

 rang only depends on C++ standard library, unistd.h system header on unix and
 windows.h & io.h system headers on windows based systems. In other words, you
 don't need any 3rd party dependencies.
 */

//#include "./headers/animals.hpp"
#include "./headers/console.hpp"
#include "./headers/json.hpp"
#include "./headers/rang.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;
using namespace rang;

consoleSize console_size; // used to store the size of console (width=cols and
                          // height=rows)

/**
 * partialMatch
 *
 * Description:
 *      Finds partial matches in a json and returns them. It
 *      does matter where in the string the match is, only returns
 *      those found with the match as the prefix.
 * Params:
 *      json            array       - json to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> partialMatch(nlohmann::json array, string substring) {
  vector<string> matches;   // to hold any matches
  //size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found. 

  if (substring.size() == 0) {
    return matches;
  }

  for (auto &element : array.items()) {       //iterate for all elements in the json file
      string key = element.key();

      // Check if the key contains the partialKey substring
      if (key.find(substring) != string::npos) {
        for(int i = 0; i < substring.length(); i++){
          if(key[i] == substring[i] && i == substring.length() - 1){  //checking if the substring matches the prefix
            matches.push_back(key);      //adding key to matches
          }
          //check if substr matches prefix, but not the entire substr has been checked
          else if(key[i] == substring[i] && i != substring.length() - 1){   
          }
          else{                         // if substr does not match, break out
            break;
          }
        }
      }
  }
  return matches;
}

/**
* Prints a long background row of gray, with text centered.
* Not a good function since colors are hard coded, but using
* rang, I don't want to invest the time to figuere out how to
* interact with rang's enumerated class types and ostream.
* I guess you could add a switch statement to change background
* color:
* switch(color){
  "black" : cout<<bgB::black;
            break;
  "red" : cout<<bgB::red;
          break;
  ...
  ...
  ...
}
But still not a good solution.
*/
void titleBar(string title, int length = console_size.width) {
  string padding = string((length / 2) - (title.size() / 2), ' ');
  title = padding + title + padding;
  cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
}

/**
 * horizontalBar
 *
 * Description:
 *      Prints a horizontal bar of a given length
 * Params:
 *      int length - length of the bar
 * Returns:
 *      void
 */
void horizontalBar(int length = console_size.width) {
  string line = string(length, '_');
  cout << fg::gray << line << fg::reset << bg::reset << endl;
}

/**
 * printMatches
 *
 * Description:
 *      Prints the matches to the screen.
 * Params:
 *      vector<string> matches - vector of matches
 * Returns:
 *      void
 */
void printMenu(vector<string> options) {
  int i = 1;
  for (auto s : options) {
    cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
         << s << fg::reset << bg::reset << endl;
    i++;
  }
  cout << fg::reset << bg::reset;
}

/**
 * printHighlightedSubstr
 *
 * Description:
 *      Given a word, print the substr underlined and red vs blue for the rest
 * of the word.
 * Params:
 *      string word - word to print
 *      string substr - substring to highlight in red
 *      int loc - location of substr in word
 * Returns:
 *      void
 */
void printHighlightedSubstr(string word, string substr, int loc) {
  for (int j = 0; j < word.size(); j++) {
    // if we are printing the substring turn it red
    if (j >= loc && j <= loc + substr.size() - 1) {
      cout << fg::red << style::underline << word[j] << fg::blue
           << style::reset;
    } else {
      cout << fg::blue << word[j] << fg::reset << style::reset;
    }
  }
}

/**
 * printCurrent
 *
 * Description:
 *      Prints the current key pressed and the current substr to the screen.
 * Params:
 *      char k - last character pressed.
 *      string word - current substring being printed.
 * Returns:
 *      void
 */
void printCurrent(char k, string word) {
  cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
       << fgB::yellow;
  if (int(k) == 127) {
    cout << "del";
  } else {
    cout << k;
  }
  cout << " = " << (int)k << fg::reset << endl;
  cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
       << fgB::blue << word << fg::reset << style::reset << endl;
  cout << endl;
}

/**
 * errorMessage
 *
 * Description:
 *      Prints an error message to the screen.
 * Params:
 *      string message - message to print
 * Returns:
 *      void
 */
void errorMessage(string message) {
  cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
  sleep(1);
}

using json = nlohmann::json;

void saveWords(json j) {
    ofstream fout;
    fout.open("./data/words.txt");

    for (auto &element : j.items()) {
        string key = element.key();
        fout << key << "\n";
    }
}

/**
 * loadJsonFile
 *
 * Description:
 *      Opens a json file
 * Params:
 *      string filepath - path to the json file to open
 * Returns:
 *      json variable that contains the file opened
 */
json loadJsonFile(string filePath) {

    // Load your JSON object as shown in previous examples
    ifstream fileStream(filePath);
    //string partialKey = "";
    json myJson;
    if (fileStream.is_open()) {
        fileStream >> myJson;
        fileStream.close();
    } else {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }
    return myJson;
}

/**
 * printDef
 *
 * Description:
 *      Prints the definition of a word to the console
 * Params:
 *      json array - json to search through
 *      string substring - current string entered by the user
 * Returns:
 *      void
 */
void printDef(nlohmann::json array, string substring){
  for (auto &element : array.items()) {       //iterate for all elements in the json file
      string key = element.key();

      // Check if the key contains the partialKey substring
      if (key.find(substring) != string::npos) {
        //printing the definition of the word
        cout << key << " -> " << element.value() << endl;
      }
  }
}

int main() {
  console_size = getConsoleSize(); // get width and height of console
  char k;                          // holder for character being typed
  string key;                      // string version of char for printing
  string substr = "";   
  nlohmann::json myJSON = loadJsonFile("./data/dictionary.json"); // pathing the json file to a variable
                                  // var to concatenate letters to
  //vector<string> animals = loadAnimalsFast(); // array of animal names
  vector<string> matches; // any matches found in vector of animals
  int loc;                // location of substring to change its color
  bool deleting = false;
  string str = "";
  vector<string> mainMenu;
  mainMenu.push_back("Type letters and watch the results change.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter. (this is for real assignment.");

  clearConsole();
  titleBar("Getch Example", console_size.width);
  printMenu(mainMenu);

  // While capital Z is not typed keep looping

  while ((k = getch()) != 'Z') {

    clearConsole();
    titleBar("Getch Example", console_size.width);
    printMenu(mainMenu);
    // Checking if the user pressed enter and there is only one result
    if((int)k == 10 && matches.size() == 1){
      printDef(myJSON, substr); // Printing the definition to the found word then breaking out of the loop
      break;
    }

    //checking if the user pressed the space key
    if((int)k == 32){
      substr += " ";
    }

    // Tests for a backspace and if pressed deletes
    // last letter from "substr".
    if ((int)k == 127) {
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
    } else {
      deleting = false;
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) {
        if((int)k == 32){           // checking if user used the space bar
          substr += "";             // adding the space to the substring
        }
        else{                       // if not alphabet, print error message
          errorMessage("Letters only!");
        }
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      substr += k; // append char to substr
    }
    horizontalBar();
    printCurrent(k, substr);

    // Find any animals in the array that partially match
    // our substr word
    matches = partialMatch(myJSON, substr);

    if ((int)k != 32) { // if k is not a space print it

      key = to_string(k);

      horizontalBar();

      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matches.size() << style::reset
           << fg::reset << endl
           << endl;

      for (auto &c : substr)
        c = tolower(c);
      // This prints out all found matches
      for (int i = 0; i < matches.size(); i++) {
        if(i == 10)         // only printing out first 10 matches found
          break;
        // find the substring in the substr
        loc = matches[i].find(substr);
        // if its found
        if (loc != string::npos) {
          printHighlightedSubstr(matches[i], substr, loc);
        }
        cout << " ";
      }
      cout << fg::reset << endl << endl << endl << endl;
      if (matches.size() == 1) {
        cout << "done? (hit enter)" << endl;
        // if user has reached one word, and hitting enter to end program
      }
    }
  }
  return 0;
}