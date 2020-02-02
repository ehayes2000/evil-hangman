/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author:

    last modified: 3/7/2019
*/

#include "hangman.h"
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <ctime>
using namespace std;

// constructor
hangman::hangman() {
    srand(unsigned(time(0)));
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int word_length, vector<string> words, bool show_words) {
    _numGuesses = num_guesses;
    _wordLength = word_length;
    _showWords = show_words;
    _possibleWords = words;
    string blank(_wordLength, '-');
    _displayWord = blank;

}

bool hangman::get_showWords() {
    return _showWords;
}

vector<string> * hangman::get_family(){
    return &_possibleWords;
}

// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased

bool hangman::process_guess(char c) {
    string largestFamily = _findLargestFamily(c);
    _guessedLetters.insert(c);
    if (largestFamily == _displayWord){
        _removeWordsWithC(c);
        _numGuesses --;
        _displayWord = largestFamily;
        return false;
    }
    _displayWord = largestFamily;
    _removeWordsWithoutDisplayWord(c);
    return true;
}

// This function removes all words from _possible words that do not have the pattern given by _displayWords
// ex if u was guessed and u was in a 5 letter word _displayWord = "---u-"
// the function would remove any word without u in index 3
// the function would also remove any words with u in any index other than 3
void hangman::_removeWordsWithoutDisplayWord(char c) {
    _tempWords = _possibleWords;
    _possibleWords.clear();
    for (string word : _tempWords) {
        for (int i = 0; i < _wordLength; i++) {
            // if the word being tested does not equal the display word where the display word is known do not re add it
            if (word[i] != _displayWord[i] && _displayWord[i] != '-') {
                break;
            }
            // if the word being tested has a char c in the wrong place do not re add it
            if (word[i] == c && _displayWord[i] != c) {
                break;
            }
            // if the loop has not yet been broken and i is the last index, add the word to _possibleWords
            if (i == _wordLength - 1) {
                _possibleWords.push_back(word);
            }
        }
    }
}
// call this if letter was not in word to remove all words containing char c
void hangman::_removeWordsWithC(char c) {
    _tempWords = _possibleWords;
    _possibleWords.clear();
    for (string word : _tempWords){
        if (word.find(c) == string::npos){
            _possibleWords.push_back(word);
        }
    }
}


string hangman::_findLargestFamily(char c) {
    map<string, int> families;
    string tempWord, largestFamily;
    int largestFamilySize = 0;
    for (string word : _possibleWords){
        tempWord = _displayWord;
        for (int i = 0; i < _wordLength; i ++) {
            if (word[i] == c && tempWord[i] == '-') {
                tempWord[i] = c;
            }
        }
        families[tempWord] ++;
    }


    for (auto x : families){
        if (x.second > largestFamilySize){
            largestFamily = x.first;
            largestFamilySize = x.second;
        }
    }
    return largestFamily;
}

// get_display_word()
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return _displayWord;
}


// get_guesses_remaining()
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return _numGuesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    string str = "";
    for (auto i : _guessedLetters){
        str += i;
    }
    return str;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    if (_guessedLetters.count(c) >= 1){
        return true;
    }
    else {
        _guessedLetters.insert(c);
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for (char letter : _displayWord){
        if (letter == '-'){
            return false;
        }
    }
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if (_numGuesses <= 0) {
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    int index = rand() % _possibleWords.size();
    return _possibleWords.at(index);
}


