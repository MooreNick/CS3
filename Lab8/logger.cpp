// Nicholas A Moore
// CSIII
// Lab 8
// Part I

#include "logger.hpp"

void appendText(Logger& singleObj, const std::string& temp) {
	singleObj.report(temp);
}
/*
int main(int argc, char* argv[]) {

	if (argc != 2) { // make sure it was executed with txt file
		std::cout << "Incorrect number of aguments";
		exit(1);
	}

	Logger* log = Logger::instance(); // make single instance
	std::fstream textFile;
	textFile.open(argv[1], std::fstream::out | std::fstream::app); // open for appending

	if (!textFile.is_open()) { // check it actually opened
		std::cout << "Error opening file";
	}

	log->assignTextFile(textFile); // assign payload

	log->report("Hello"); // append literal
	std::string test = "World";
	log->report(test); // append named
	log->report("test"); // append literal

	std::string testFunc = "testing function with named constant";

	appendText(*log, "testing function with literal constant"); // literal
	appendText(*log, testFunc); // function named

	textFile.close(); // close file

	return 0;
}*/