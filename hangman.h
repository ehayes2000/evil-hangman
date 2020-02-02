#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: 

    last modified: 9/24/2017
*/

#include <string>
#include <vector>
#include <set>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses, int word_length,vector<string> words, bool show_words);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    bool get_showWords();

    vector<string> * get_family();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // returns true if char is in word

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

private:
    set<char> _guessedLetters;
    int _numGuesses, _wordLength;
    vector<string> _possibleWords, _tempWords; // list of possible words
    string _displayWord; // display word
    bool _showWords;
    string _findLargestFamily(char c); // finds the largest family of words containing c and returns
    // a string containing the patter of c ie "_cc_" , "____", or "c___"
    void _removeWordsWithoutDisplayWord(char c); //change possible words to reflect display word
    void _removeWordsWithC(char c);
};



#endif
