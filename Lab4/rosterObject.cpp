// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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


class Student {
public:

    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    Student(string firstName, string lastName, list<string> courses) :
        firstName_(firstName), lastName_(lastName), courses_(courses) {}

    // move constructor, not really needed, generated automatically
    Student(Student&& org) noexcept :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_)),
        courses_(move(org.courses_)) {}

    // force generation of default copy constructor
    Student(const Student& org) = default;

    void setCourse(string course) { courses_.push_back(course); }

    string print() const; //{ return firstName_ + ' ' + lastName_; } //outside def

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
    list<string> courses_;
};

string Student::print() const {
    string result;
    result = firstName_ + ' ' + lastName_;
    for (auto& it : courses_) {
        result += ' ';
        result += it;
    }
    return result;
}




// reading a list from a fileName
void readRoster(vector<list<Student>>& roster, string fileName);
// printing a list out
void printRoster(const vector<list<Student>>& roster);

void removeDropouts(vector<list<Student>>& roster, vector<list<Student>>& dropouts);

int main(int argc, char* argv[]) {


    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    // vector of courses of students
    vector <list<Student>> roster;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(roster, argv[i]);
    }

    cout << "Students not sorted and dropouts not removed" << endl;
    printRoster(roster);
    
    // reading in dropouts
    vector<list<Student>> dropouts;
    readRoster(dropouts, argv[argc - 1]);

    removeDropouts(roster, dropouts);

    std::sort(roster.begin(), roster.end());


    cout << endl << endl << endl << "Students sorted by last name and dropouts removed: " << endl;
    printRoster(roster);

}


void readRoster(vector<list<Student>>& roster, string fileName) {
    ifstream course(fileName);
    string first, last, className;

    for (auto e : fileName) { // once a '.' denotes file extension
        if (e != '.') {
            className += e; // concat until file extension
        }
        else if (e == '.')
            break;
    }
    

    while (course >> first >> last) {
        Student temp(first, last);
        list<Student> singleStudent; // for compatibility with the vector of lists of students

        bool newStudent = true;

        for (auto &it : roster) {
            if (it.front() == temp) { // comparing names
                newStudent = false; // not a new student
                it.front().setCourse(className); // push in additional class
                break; // stop looking
            }
        }

        if (newStudent) {
            temp.setCourse(className);
            singleStudent.push_back(move(temp));// invoking defined move constructor
            roster.push_back(move(singleStudent));
        //    singleStudent.clear();

        }
    }

    course.close();
}




void removeDropouts(vector<list<Student>>& roster, vector<list<Student>>& dropouts) {
    for (auto itRoster = roster.begin(); itRoster != roster.end();) {
        for (auto itDropouts : dropouts) {
            if (itRoster[0].front() == itDropouts.front()) {
                itRoster = roster.erase(itRoster);
            }
        }
        ++itRoster;
    }
}


// printing a list out
void printRoster(const vector<list<Student>>& roster) {
    for (const auto& itr : roster) { // itr for list
        for (const auto& student : itr) { // each student
            cout << student.print() << endl;
        }
    }
        
}