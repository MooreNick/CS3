// Nicholas A Moore
// Lab 1
// Computer Science III
// 01/20/2023

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[]) {

	if (argc < 3) { // One for exe and one for each file
		std::cout << "Error, not enough arguments." << std::endl;
		return -1;
	}

	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}

	std::string fileOneContent; // Contents for both files
	std::string fileTwoContent;

	std::ifstream file1(argv[1]); // File 1
	std::ifstream file2(argv[2]); // File 2

	if (!file1.is_open()) { //Making sure both files were properly opened
		std::cout << "Unable to open first file." << std::endl;
		return -1;
	}

	if (!file2.is_open()) {
		std::cout << "Unable to open second file." << std::endl;
		return -1;
	}

	int length = -1; // Holds position of difference
	int lineNumberOne = 0; // Line counters for each file
	int lineNumberTwo = 0;

	while (!file1.eof() || !file2.eof()) { // Not at end of either

		if (file1.eof()) { // End of file 1
			fileOneContent = ""; // Empty string
		}
		else {
			getline(file1, fileOneContent);
			++lineNumberOne;
		}

		if (file2.eof()) { // End of file 2
			fileTwoContent = ""; // Empty string
		}
		else {
			getline(file2, fileTwoContent); // Get next line
			++lineNumberTwo;
		}


		if (fileOneContent != fileTwoContent) { // Difference in line

			/* Need to iterate through longer of two strings
			* Conditional Operator used to find the longer string
			*/
			int maxIteration = fileOneContent.length() > fileTwoContent.length() ? fileOneContent.length() : fileTwoContent.length();

			for (int i = 0; i < maxIteration; ++i) {
				if (fileOneContent[i] != fileTwoContent[i]) { // Found position within line
					length = i; // Keeping that position
					break; // Only one difference is needed
				}
			}
	    } 
	

		if (length != -1) // If length is different than -1 we located a difference
			break; // Exit the while loop, only 1 difference is needed

	}

	if (length != -1) { // Information is only printed when a difference is located

		std::string diffString(length + 14, ' '); // +14 is the offset due to filename and the : symbols and ' ' (space) symbols
		diffString = diffString + '^';

		std::cout << argv[1] << ": " << lineNumberOne << ": " << fileOneContent << std::endl;;
		std::cout << argv[2] << ": " << lineNumberTwo << ": " << fileTwoContent << std::endl;;
		std::cout << diffString << std::endl;

	}


	file1.close();
	file2.close();

	return 0;

}
