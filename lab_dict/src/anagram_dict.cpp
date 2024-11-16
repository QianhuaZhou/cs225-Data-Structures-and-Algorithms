/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    std::ifstream input(filename);
    string word;
    string sorted;
    if(!input.is_open()) throw std::runtime_error("Fail to open the file.");
    while(input >> word){
        sorted = word;
        sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(word);
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(const string& word : words){
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        std::cout << "sorted = " << sorted << " word = " << word << std::endl;
        dict[sorted].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string temp = word;
    sort(temp.begin(), temp.end());
    auto it = dict.find(temp);//can't direcly use word here, not sure why
    if(it != dict.end()) return it->second;//dict--const, can't use operator []
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for(const auto& [str, vec] : dict){
        if(vec.size() > 1) ret.push_back(vec);
    }
    return ret;
}
