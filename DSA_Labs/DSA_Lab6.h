/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:	Kevin Blackmon

Created:		02.15.2021
Last Modified:	02.26.2021
Purpose:		Usage of the std::unordered_map class
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Master toggle
#define LAB_6	1

// Individual unit test toggles
#define MAP_POPULATE_LETTER_VALUES	1
#define MAP_GET_LETTER_VALUE		1
#define MAP_GET_WORD_VALUE			1
#define MAP_CREATE_PAIR				1
#define MAP_LOAD_FILE				1
#define MAP_FIND_WORD_SCORE			1

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

#if LAB_6

class DSA_Lab6 {

	friend class DSA_TestSuite_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26];
	std::unordered_map<std::string, int> mScrabbleMap;

public:

	// In Scrabble, each letter has a value associated with it.
	// This method will populate the array of letter values.
	//
	// In:	_letterValues		The array of 26 values
	void PopulateLetterValues(const int* _letterValues) {
		// TODO: Implement this method
		for (size_t i = 0; i < 26; i++)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	// Retrieve the value of a particular letter
	// 
	// In:	_letter			The letter to get the score for
	//
	// Return:	The score value for the letter passed in
	// NOTE:	The letter passed in will always be upper-case
	int GetLetterValue(char _letter) const {
		// TODO: Implement this method
		return mLetterValues[_letter - 65];
	}

	// Get the value of a word
	//		This is done by adding up the values of each letter in the word
	//
	// In:	_word		The word to get the value of
	//
	// Return: The total value of the word
	int GetWordValue(const std::string& _word) const {
		// TODO: Implement this method
		int word = 0;
		for (size_t i = 0; i < _word.length(); i++)
		{
			word += GetLetterValue(_word[i]);
		}
		return word;
	}

	// Create a pair to add into the scrabbleMap
	//		This will have a "first" of the word, and a "second" of the total score
	//
	// In:	_word		The word for the pair
	//
	// Return: A pair that contains the word and the total score
	std::pair<std::string, int> CreatePair(const std::string& _word) const {
		// TODO: Implement this method
		unsigned short Wordval = GetWordValue(_word);
		std::pair<std::string, int> pair;
		pair.first = _word;
		pair.second = Wordval;
		return pair;
	}

	// Load a file containing all of the possible scrabble words, along with their values
	//		This file will contain one word per line
	// In:	_filename	The name of the file to load
	//
	// Note: You may want to use one or more existing methods to help.
	void LoadWords(const char* _filename) {
		// TODO: Implement this method
		std::string currLine;
		std::pair<std::string, int> pair;

		std::ifstream file(_filename);
		while (true)
		{
			std::getline(file, currLine);
			mScrabbleMap.insert(CreatePair(currLine));
			if (file.eof())
				break;
		}
	}

	// Searches for a word in the map, and retrieves the score for that word
	//
	// In:	_word			The word to search for
	//
	// Return: The word score for _word (or -1 if not found)
	int FindValueInMap(const std::string& _word) {
		// TODO: Implement this method
		auto iter = mScrabbleMap.find(_word);
		if (iter != mScrabbleMap.end())
		{
			return iter->second;
		}
		return -1;
	}
};

#endif	// End LAB_6