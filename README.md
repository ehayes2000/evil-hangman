# evil-hangman
A C++ program to make you lose hangman

**Overview**


This project is a text based hangman game rigged to remove words containing the users guessed letters from the possible word pool.
The project is organized into one class (hangman.h) and a main.cpp containing four independent helper functions. 

The program works by choosing its word based on the letters the user has guessed instead of choosing a word at the beggining of the game 
like in a traditional game of hangman. With every guess the user makes, the program calculates if there are more words with a pattern 
of the guessed letter or more words without. Then the program chooses the larger family. Here's an example with a three letter word:


![alt text](https://github.com/ehayes2000/evil-hangman/blob/master/hangman-play-through.png)











