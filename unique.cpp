/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Bobby Georgiou
 * Date        : 09/22/2018
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/**
 * Return true if all characters in the string are lowercase letters; 
 * otherwise, return false
 */
bool is_all_lowercase(const string &s) {
    for (const char &c : s) {
        if (!islower(c)) { return false; }
    }
    return true;
}

/**
 * Return true if all letters in a specified string are unique or 
 * false if there are repeated letters using bitshifting and 
 * bitwise operators
 */
bool all_unique_letters(const string &s) {
    unsigned int bit_vector = 0;
    for (const char &c : s) {
        unsigned int setter = 1 << (c - 'a'); // determine place of current letter in bit vector
        if (bit_vector & setter) { // AND, check if setter bit has been flagged
            return false;
        } else {
            bit_vector |= setter; // OR, flag current bit at setter
        }
    }
    return true;
}

/**
 * Read and parse command line arguments; call other functions
 * to produce correct output
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    } else if (argc > 2) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }
    if (!is_all_lowercase(argv[1])) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    if (all_unique_letters(argv[1])) {
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
