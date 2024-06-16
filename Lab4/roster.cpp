// Nicholas A Moore
// CSIII
// 02/10/2023
// Lab 4 Roster Class Schedule

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>& roster, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster);

// remove dropouts
void removeDropouts(vector<list<string>>& roster, vector<list<string>> dropouts);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last"
            << endl;
        exit(1);
    }

    vector<list<string>> roster; 

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(roster, argv[i]);
    }
    cout << "All students, including dropouts, no duplicates" << endl;
    printRoster(roster);


    // reading in dropouts
    vector<list<string>> dropouts;
    readRoster(dropouts, argv[argc - 1]);
    removeDropouts(roster, dropouts);

    cout << endl << endl << endl;
    cout << "All students, sorted by first name, excluding dropouts" << endl;


    std::sort(roster.begin(), roster.end()); // sort func included in algorithms, sorts from starting iterator to ending
    
    printRoster(roster);
   
    return 0;
}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, string fileName) {
    ifstream course(fileName);
    string first, last, className, studentName;
    list<string> singleStudent;

    for (int i = 0; i < fileName.length(); ++i) { // This loop obtains the name of the class
        if (fileName[i] != '.') { // '.' means we have reached the file extension
            className += fileName[i];
        }
        else {
            break;
        }
    }
    while (course >> first >> last) {
        studentName = first + ' ' + last; // retreieve name
        singleStudent.push_back(studentName); // put it into compatible container
        bool newStudent = true; // assume its new student

        for (auto it = roster.begin(); it != roster.end(); ++it) {
            if (it[0].front() == singleStudent.front()) { // student already exists
                it->push_back(className); // add class name
                newStudent = false; // wasn't new student
                singleStudent.clear(); // reset student
                break;
            }
        }

        if (newStudent) {
            singleStudent.push_back(className); // add class info
            roster.push_back(singleStudent); // add student
            singleStudent.clear(); // reset student
        }


    }
    course.close();
}

void removeDropouts(vector<list<string>>& roster, vector<list<string>> dropouts) {
    for (auto rosterIt = roster.begin(); rosterIt != roster.end();) {
        for (auto dropIt : dropouts) {
            if (rosterIt[0].front() == dropIt.front()) { // compaires names
                rosterIt = roster.erase(rosterIt); // reassign iterator to avoid invalidation
            }
        }
        ++rosterIt;
    }
}

//vector of lists of strings
//each index can be a list of strings
//each list of strings should be student names->class names
//below code works as you would expect for reference
// 
//singleStudent.push_back(studentName);
//singleStudent.push_back(className);
//roster.push_back(singleStudent);


// printing a list out
void printRoster(const vector<list<string>>& roster) {
    for (const auto& it : roster) { // enter vector
        for (const auto& itr : it) // enter individual list
            cout << itr << ' ';
        cout << endl;
    }
}
