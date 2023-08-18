/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <algorithm>
#include <fstream>
#include <unordered_map>

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
    ifstream words(filename);
    string word;
    if (words.is_open()) {
        while (getline(words, word)) {
            add_word_to_dict(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for (const string& word : words) {
        add_word_to_dict(word);
    }
}

/**
 * @param word The word to add to the dictionary
 * Adds the word as a (key, value) pair to the dictionary.
 * NOTE: word is the value. You will need to decide an appropriate key
 * for the word.
 */
void AnagramDict::add_word_to_dict(const std::string& word)
{
    int length1 = word.length();

    for(auto it = dict.begin(); it != dict.end(); it++) {
        string keyWord = it->first;

        int length2 = keyWord.length();
        // std::unordered_map<char, int> m;
        std::map<char, int> m;


        if(length1 != length2){
            // don't do anything
        } else {
            for (int i = 0; i < length1; i++) {
                m[word[i]]++;
                }
            for (int i = 0; i < length2; i++) {
                if(m.find(keyWord[i]) != m.end()){

                    m[keyWord[i]]--;

                    if(m[keyWord[i]] == 0){
                        m.erase(m[keyWord[i]]);
                        }
                    }
                } 
        }

        if(m.size() == 0){
            // rather than saying dict[keyword], can also say it->secon
            std::vector<std::string> & temp = dict[keyWord];
            temp.push_back(word);
            return;
        }
    }

    std::vector<std::string> init;
    dict[word] = init;

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    int length1 = word.length();
    std::vector<std::string> out;

    for(auto it = dict.begin(); it != dict.end(); it++) {
        string keyWord = it->first;

        int length2 = keyWord.length();
        // std::unordered_map<char, int> m;
        std::map<char, int> m;


        if(length1 != length2){
            // don't do anything
        } else {
            for (int i = 0; i < length1; i++) {
                m[word[i]]++;
                }
            for (int i = 0; i < length2; i++) {
                if(m.find(keyWord[i]) != m.end()){

                    m[keyWord[i]]--;

                    if(m[keyWord[i]] == 0){
                        m.erase(m[keyWord[i]]);
                        }
                    }
                } 
        }

        if(m.size() == 0){
            out = it->second;
            return out;
        }
    }

    
    return out;
}




/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> out;

    for(auto it = dict.begin(); it != dict.end(); it++){
        vector<string> temp = it->second;
        if(temp.size() >= 2){
            out.push_back(temp);
        }
    }
    return out;
}
