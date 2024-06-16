// Nicholas A Moore
// 01/25/2023
// CSIII Lab 2 - Word Count

#include "WordList.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main(int argc, char* argv[]) {

	if (argc < 2) { // Ensure command line argument
		std::cout << "Error, include file name on command line." << std::endl;
		return -1;
	}

	std::ifstream file1(argv[1]);

	if (!file1.is_open()) { // Ensure file opens
		std::cout << "Error, unable to open specified file." << std::endl;
		return -1;
	}

	WordList allWords;
	std::string word;
	
	while (!file1.eof()) { // While there is more in file

		char ch;
		file1.get(ch); // Obtain one char
		if (file1.eof()) break; // If that was the end of the file exit

		
//		if (ch != '!' && ch != '?' && ch != '.' && ch != ' ' && ch != '\n' && ch != ';' && ch != ',') { // Checking char against punctuation
//			word = word + ch; // Concat char to running string
//		}
		
		if (isalnum(ch) != 0) { // Checking against puncutation
			word = word + ch;
		}

		else {

			if (word != "") {
				allWords.addWord(word); // Put word into list of words
				word = ""; // Reset string
			}
			
		}
	}
	if(word != "") // Incase it ended on non alphanumeric
	allWords.addWord(word); // This is encountered on eof, pushes last word into list
	allWords.print();

	file1.close();

	return 0;
}
