// Jackie Yee
// Create and Hash
// CSCI 335

#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"

using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    hash_table.MakeEmpty();
    
    /*
    creates ifstream object readF and opens word file, reads through file and inserts getString
    to hash table
    */
    ifstream readF;
    readF.open(words_filename);
    string getString;
    if (!readF.is_open())
    {
        cout << "File not found or unable to read: " << words_filename << endl;
    }
    while (getline(readF, getString))
    {
        hash_table.Insert(getString);
    }

    readF.clear();
    readF.close();

    cout << "number_of_elements: " << hash_table.getCurrentSize() << endl;
    cout << "size_of_table: " << hash_table.getSize() << endl;
    cout << "load_factor: " << (double) hash_table.getCurrentSize()/hash_table.getSize() << endl;
    cout << "collisions: " << hash_table.getCollisions() << endl;
    cout << "avg_collisions: " << (double) hash_table.getCollisions()/hash_table.getCurrentSize() << endl << endl;


    /*
    ifstream object matchF is created and query file is opened,
    when the string in query file matches a collision is created 
    and stored into the hash table
    */
    ifstream matchF;
    matchF.open(query_filename);

    if (!matchF.is_open())
    {
        cout << "File not found or unable to read: " << query_filename << endl;
    }
    while (getline(matchF, getString))
    {
        hash_table.resetCollisions();
        if (!hash_table.Contains(getString))
        {
            cout << getString << " Not_Found " << hash_table.getCollisions() + 1 << endl;
        }
        else
        {
            cout << getString << " Found " << hash_table.getCollisions() + 1 << endl;
        }
    }
    matchF.clear();
    matchF.close();
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename,
       			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table;
	TestFunctionForHashTable(double_probing_table, words_filename,
	 			 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
