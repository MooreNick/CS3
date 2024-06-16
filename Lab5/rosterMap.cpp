// Nicholas A Moore
// CSIII Lab 5
// 02/16/2023

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    // move constructor, not really needed, generated automatically
    Student(Student&& org) noexcept :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}

    // force generation of default copy constructor
    Student(const Student& org) = default;

    string print() const { return firstName_ + ' ' + lastName_; }

    // needed for unique() and for remove()
    friend bool operator== (Student left, Student right) {
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    // needed for sort()
    friend bool operator< (Student left, Student right) {
        return left.lastName_ < right.lastName_ ||
            (left.lastName_ == right.lastName_ &&
                left.firstName_ < right.firstName_);
    }
private:
    string firstName_;
    string lastName_;
};




// reading a list from a fileName
void readRoster(std::map<Student, list<string>>&, string fileName);
// printing a list out
void printRoster(const std::map<Student, list<string>>&);

void removeDropouts(std::map<Student, list<string>>&, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    std::map<Student, list<string>> studentSchedule;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(studentSchedule, argv[i]);
    }

    removeDropouts(studentSchedule, argv[5]);

    cout << "All students, dropouts removed" << endl;
    printRoster(studentSchedule);

    return 0;
}


void readRoster(std::map<Student, list<string>>& studentSchedule, string fileName) {
    ifstream course(fileName);
    string first, last, className;
    int i = 0;
    char ch = fileName[i];

    while (fileName[i] != '.') { // obtain name of class from filename
        className += ch;
        ++i;
        ch = fileName[i];
    }
    
    while (course >> first >> last) {
        Student temp(first, last);

        auto it = studentSchedule.find(temp); // Check for student

        if (it != studentSchedule.end()) { // found the student
            it->second.push_back(className); // add class to the list
        }
        else { // new student
            list<string> tempClass; // create list for compatibility
            tempClass.push_back(className); // put class name in list
            studentSchedule.insert(std::make_pair(temp, tempClass)); // insert in map
        }
    }
    course.close();
}

void removeDropouts(std::map<Student, list<string>>& studentSchedule, string fileName) {
    ifstream dropouts(fileName);
    string first, last;

    while (dropouts >> first >> last) {
        Student temp(first, last);
        studentSchedule.erase(temp);
    }
}

// printing a list out
void printRoster(const std::map<Student, list<string>>& studentSchedule) {
    auto it = studentSchedule.cbegin(); // for names
    while (it != studentSchedule.cend()) {
        auto classIt = it->second.cbegin(); // for classes, needs reassigned each time
        cout << it->first.print() << ":"; // print name
        while (classIt != it->second.cend()) {
            cout << *classIt << ' '; // print all classes
            ++classIt;
        }
        cout << endl;
        ++it; // next name
    }
}
