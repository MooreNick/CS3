// Nicholas A Moore
// CSIII
// Lab 8
// Part I

#ifndef CS3_LAB8_SINGLETON_
#define CS3_LAB8_SINGLETON_

#include <string>
#include <iostream>
#include <fstream>

// Meyer style
class Logger {
public:

	static Logger* instance() {
		static Logger singleObj;
		return &singleObj;
	}

	void assignTextFile(std::fstream&);

	void report(const std::string&);

	~Logger() {};
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete; // deleting methods

private:
	Logger() {};
	std::fstream *file_;
};

void Logger::report(const std::string& temp) {
	*file_ << temp;
}

void Logger::assignTextFile(std::fstream &in) {
	file_ = &in;
}

#endif