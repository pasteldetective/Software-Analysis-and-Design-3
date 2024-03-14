// Jackie Yee
// Spell Checker
// CSCI 335

#include <fstream>
#include <iostream>
#include <string>

#include <cctype> //for isalnum

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

/*
for each char in word from document_file, the nonalphanumeric chars are
removed, the capitalized chars replaced by lowercase chars
*/
void RemoveNonAlphaNumChars(string& word) {
  string replacement;
  for (char c : word) 
  {
    /*
    isalnum is used to check for characters that are alphanumeric
    digits and numbers are represented while special chars are not
    */
    if (std::isalnum(c)) 
    {
      replacement += std::tolower(c); //converts c is a lowercase
    }
  }
  word = replacement;
}

/*
checks for case A for word in a dictionary, for each word in document_file
each char A-Z is added to word and checked to see if in the dictionary
*/
void caseA(const HashTableDouble<string>& dictionary, const string& word) {
  for (int i = 0; i <= word.length(); i++) 
  {
    for (char c = 'a'; c <= 'z'; c++) //iterate chars
    {
      string modified = word;
      modified.insert(i, 1, c); //insert(position, size, val)
      if (dictionary.Contains(modified)) //from quadratic probing
      {
        std::cout << "** " << word << " -> " << modified << " ** case A" << std::endl;
      }
    }
  }
}

/*
checks for case B for word in a dictionary, for each word in document_file
the char in word is removed and checked to see if in the dictionary
*/
void caseB(const HashTableDouble<string>& dictionary, const string& word) {
  for (int i = 0; i < word.length(); ++i) 
  {
    string modified = word;
    modified.erase(i, 1);
    if (dictionary.Contains(modified)) 
    {
      std::cout << "** " << word << " -> " << modified << " ** case B" << std::endl;
    }
  }
}

/*
checks for case C for word in a dictionary, for each word in document_file
the char in word is swapped with adjacent char and checked to see if in the dictionary
*/
void GeneratePossibleCorrections(const HashTableDouble<string>& dictionary, const string& word) {
  for (int i = 0; i < word.length() - 1; i++) 
  {
    string modified = word;
    std::swap(modified[i], modified[i + 1]);
    if (dictionary.Contains(modified)) 
    {
      std::cout << "** " << word << " -> " << modified << " ** case C" << std::endl;
    }
  }
}

// Creates and fills double hashing hash table with all w from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Open the dictionary file with dictionary
  std::ifstream dictionary(dictionary_file);
  //If dictionary is unable to open, return an empty hash table
  if (!dictionary.is_open()) 
  {
    return dictionary_hash;
  }
  string readable;
  //readable words are insered into the hash table
  while (dictionary >> readable) 
  {
    dictionary_hash.Insert(readable);
  }
  dictionary.close();
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) 
{
  std::ifstream readFile(document_file);
  if (!readFile.is_open()) 
  {
    std::cout << "Unable to open file: " << document_file << std::endl;
    return;
  }

  string wordIterator; 
  while (readFile >> wordIterator)
  {
    RemoveNonAlphaNumChars(wordIterator);

    // Check if the word is in the dictionary
    if (!dictionary.Contains(wordIterator)) 
    {
      cout << wordIterator << " is INCORRECT" << endl;
      // Generate possible corrections by adding one character at each position
      caseA(dictionary, wordIterator);
      caseB(dictionary, wordIterator);
      caseC(dictionary, wordIterator);
    }
    else
    {
      cout << wordIterator << " is CORRECT" << endl;
    }
  }
  readFile.close();
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}