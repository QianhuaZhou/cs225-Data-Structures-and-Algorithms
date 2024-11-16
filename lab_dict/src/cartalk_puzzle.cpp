/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                                                         const string &word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    std::ifstream wordsFile(word_list_fname);
    if(!wordsFile.is_open()) throw std::runtime_error("Fail to open the file.");
    string word;
    if(wordsFile.is_open()){
        //while(getline(wordsFile, word)){
        while(wordsFile >> word){//both correct
            string origin = word;
            string rm_first = word;
            string rm_second = word;
            rm_first.erase(0, 1);//remove 1 char from idx = 0
            rm_second.erase(1, 1);
            if(d.homophones(origin, rm_first) && d.homophones(origin, rm_second)){
                ret.push_back({origin, rm_first, rm_second});
            }
        }
    }
    return ret;
}
