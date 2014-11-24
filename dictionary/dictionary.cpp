/* Author:	Matt W. Martin, 4374851
 *		kaethis@tasmantis.net
 *
 * Project:	CS2010, Assignment #2
 *		        Dictionary II
 *
 * File:	dictionary.cpp */

#include "cdictionary"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

void Dictionary::getWords(){
	/* The method opens the keyboard input stream and collects a series of chars
	 * to interpret them as words.  Once a word has been assembled, it is
	 * compared with all existing Entries in the Dictionary; if it does not exist,
	 * the word is added.  This process is repeated until it encounters a newline
	 * (or 'ENTER' if receiving input manually).  */

	char letter;
	WORD word;			/* Collection of letters that make up a word.
					 * NOTE: Its contents are cleared after
					 *	 assembling each word. */

	int word_index;			/* If >= 0, reprsents the index of an Entry.
					 * If -1, means word doesn't exist. */

	bool add_word;			/* TRUE if the word was entered successfully.
					 * FALSE if Dictionary is already full. */

	bool lett_flag = false;
	bool apostrophe_flag = false;
	bool hyphen_flag = false;

	while(cin.good()){

		letter = cin.get();

		/* If letter is an alphabetic char (a letter, in other words) proceed
		 * to add it to the word. */
		if(isalpha(letter)){
			
			/* If an apostrophe was passed following a letter (indicating
			 * that it is part of a word), an apostrophe is inserted. */
			if(apostrophe_flag)
				word.append("'");

			/* Alternatively, if a hyphen was passed following a letter,
			 * a hyphen is inserted before the new letter. */
			else if(hyphen_flag) 
				word.append("-");

			// The lowercase letter is inserted at the end of the word.
			word.push_back(tolower(letter));

			lett_flag = true;
			apostrophe_flag = false;
			hyphen_flag = false;
	
		/* If an apostrophe is passed immediately after a letter, the
		 * apostrophe_flag is set. */
		} else if((lett_flag) && (!apostrophe_flag) && (letter == 39)){ 
				
			/* NOTE: A word is only considered a contraction if there
			 *	 exists a letter on both sides of the  apostrophe.
			 * 
			 *	 FOR EXAMPLE:	[ENTRY]       [OUTCOME] 
			 *			you've   ---->  you've
			 *			you'     ---->     you
			 *			've      ---->      ve   
			 *       (THIS PROGRAM MAKES NO DISTINCTION BETWEEN
			 *        THE POSESSIVE 's AND THE CONTRACTION OF A
			 *        NOUN & 's [i.e., "Matt's tablet", vs.
			 *	  "Matt's late for class."]) */

			apostrophe_flag = true;
			hyphen_flag = false;

		/* If a hyphen is passed immediately after a letter, the hyphen_flag
		 * is set. */
		} else if((lett_flag) && (!hyphen_flag) && (letter == 45)){ 
				
			/* NOTE: A word is only considered hyphenated if there
			 *	 exists a letter on both sides of the hyphen.
			 *
			 *	 FOR EXAMPLE:	[ENTRY]          [OUTCOME] 
			 *		    one-hundred  ----> one-hundred
			 *			   one-  ---->         one
			 *		       -hundred  ---->     hundred */

			hyphen_flag = true;
			apostrophe_flag = false;

		/* If a non-alphabetic character is encountered immediately following
		 * a letter, the end of the word has been reached!  */
		} else if(lett_flag){

			word_index = this -> findWord(word);

			/* If the word already exists in this Dictionary, that
			 * Entry's frequency is incremented. */
			if(word_index >= 0)
				(this -> entries[word_index]).freq++;

			/* Otherwise, as long as this Dictionary isn't full, the new
			 * word is added to this Dictionary. */
			else
				add_word = this -> addEntry(word);

			/* If the Entry was successfully entered into the Dictionary,
			 * word is cleared and all flags are reset. */
			if(add_word){
				word.clear();

				lett_flag = false;
				apostrophe_flag = false;
				hyphen_flag = false;

			/* Otherwise, the word was discarded because this Dictionary
			 * is already full: interrupt the getWords procedure. */
			} else
				return;

		// A newline (i.e. 'ENTER') indicates the end of the keyboard stream.
		} else if(letter == '\n')
			return;
	}
}

int Dictionary::addEntry(WORD word){
	/* This method adds the word as a new Entry in the Dictionary (as long as
	 * it's not full). */

	ENTRY newEntry;

	if(!this -> isFull()){

		newEntry.word = word;
		newEntry.freq = 1;

		this -> entries.push_back(newEntry);
		this -> word_index++;

		return 1;
	} else
		return 0;	// (Returns 0 if the Dictionary's already full!)
}

int Dictionary::findWord(WORD word){
	/* This method compares the word with past Entries in the Dictionary (as long
	 * as it isn't empty).  If the word exists, its index is returned.  */
	
	int word_index = 0;

	if(!this -> isEmpty()){

		while(word_index < this -> word_index){

			if(word == (this -> entries[word_index]).word)
				return word_index;
			else
				word_index++;
		}

		return -1;	// (Returns -1 if word was not found!)
	} else
		return -1;	// (Returns -1 if Dictionary is empty!)
}

int Dictionary::sortWords(){
	/* This method uses a (recursive!) insertion-sort procedure to sort the
	 * Entries in the Dictionary in alphabetical order (as long as it isn't
	 * empty). */

	Entry tmpEntry;

	if(!this -> isEmpty()){

		for(int i = 1; i < this -> word_index; i++){

			int j = (i - 1);

			if((this -> entries[j]).word > (this-> entries[i]).word){

				tmpEntry = this -> entries[j];
				this -> entries[j] = this -> entries[i];
				this -> entries[i] = tmpEntry;

				this -> sortWords();	
			}
		}

		return 1;
	} else
		return 0;	// (Returns 0 if there aren't any words to sort!)
}

int Dictionary::printWords(){
	/* This method prints the (sorted!) contents of the Dictionary (as long as it
	 * isn't empty) in a manner that's clean, simple, and and easy to look at.
	 *
	 * NOTE: If the length of a word is more than 38 characters, printWords may
	 *	 not display correctly.  In this case, it's highly recommended you
	 *	 use the dumpWords method instead. */

	int word_index = 0;

	WORD word;
	int freq;

	int FREQ_BEGINS = 46;
	int spaceCount;

	if(!this -> isEmpty()){

		this -> sortWords();	// Sort the Dictionary before printing it!

		printf(" ____  _      _   _                              \n");
		printf("|  _ \\(_) ___| |_(_) ___  _ __   __ _ _ __ _   _ \n");
		printf("| | | | |/ __| __| |/ _ \\| '_ \\ / _` | '__| | | |\n");
		printf("| |_| | | (__| |_| | (_) | | | | (_| | |  | |_| |\n");
		printf("|____/|_|\\___|\\__|_|\\___/|_| |_|\\__,_|_|   \\__, |\n");
		printf(" S T R I N G - V E C T O R   E D I T I O N |___/ \n");
		printf("-------------------------------------------------\n");
		printf(" [WORD]                                   [FREQ] \n");

		while(word_index < this -> word_index){	

			word = (this -> entries[word_index]).word;
			freq = (this -> entries[word_index]).freq;

			/* NOTE: I want the frequency to be printed starting from the
			 *	 column index stored in FREQ_BEGINS.  Because the 
			 *	 length of each word varies, the number of blank-
			 *	 spaces required to get to that column will also
			 *	 vary.  By subtracting the word's length from
			 *	 FREQ_BEGINS, we can determine the number of blank-
			 *	 spaces we need! */
			spaceCount = (FREQ_BEGINS - word.length());

			printf(" %s %*d \n", word.c_str(), spaceCount, freq);

			word_index++;
		}

		printf("\n-------------------------------------------------\n");
		printf(" [NUM. OF WORDS IN DICTIONARY: ");

		/* This prints out the number of UNIQUE words that were entered into
		 * the Dictionary.  If the Dictionary reached its full potential, the
		 * sum will literally read "MAX". */
		if(this -> isFull())
			printf("%16s]", "MAX");
	
		// Otherwise, the numerical value gets printed.
		else
			printf("%16d]", word_index);

		printf("\n-------------------------------------------------\n");
		return 1;
	} else
		return 0;	// (Returns 0 if there aren't any words to print!)
}

int Dictionary::dumpWords(){
	/* This method provides a quick-and-easy way of printing the Entries of the
	 * Dictionary at any given time (as long as it isn't empty).  (Not very
	 * pretty to look at, though, so I suggest you use this method for diagnostic
	 * purposes only.) */

	int word_index;

	WORD word;
	int freq;

	if(!this -> isEmpty()){

		for(word_index = 0; word_index < this -> word_index; word_index++){

			word = (this -> entries[word_index]).word;
			freq = (this -> entries[word_index]).freq;

			printf("[%d] %s (%d) \n", word_index, word.c_str(), freq);
		}

		return 1;
	} else
		return 0;	// (Returns 0 if there aren't any words to dump!)
}

