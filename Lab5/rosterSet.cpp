// Nicholas A Moore
// CSIII Lab 5
// 02/16/2023
/*
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>

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
void readRoster(std::set<Student>& allStudents, string fileName);
// printing a list out
void printRoster(const std::set<Student>& allStudents);

void removeDropouts(std::set<Student>& allStudents, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    std::set<Student> allStudents;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(allStudents, argv[i]);
    }

    removeDropouts(allStudents, argv[5]);

    cout << "Currently Enrolled Students" << endl;
    printRoster(allStudents);

    return 0;
}


void readRoster(std::set<Student>& allStudents, string fileName) {
    ifstream course(fileName);
    string first, last;
    while (course >> first >> last) {
        Student temp(first, last);
        allStudents.insert(temp);
    }
    course.close();
}

void removeDropouts(std::set<Student>& allStudents, string fileName) {
    ifstream dropouts(fileName);
    string first, last;
    while (dropouts >> first >> last) {
        Student temp(first, last);
        allStudents.erase(temp);
    }
}

// printing a list out
void printRoster(const std::set<Student>& allStudents) {
    for (const auto& student : allStudents)
        cout << student.print() << endl;
}*/