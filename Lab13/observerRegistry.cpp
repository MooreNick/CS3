// Nicholas A Moore
// CSIII
// Lab 13 Part II
// 04/24/2023

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry {
public:
    static void registerObserver(std::string, Observer*);
    static void deregisterObserver(std::string, Observer*);
    static void handleMessage(std::string);
private:
    static map<std::string, set<Observer*>> observerMap_;
};

// initialize the static map
map<std::string, set<Observer*>> EventRegistry::observerMap_;


class Observer {
public:
    Observer(const string& name) : name_(name) {}
    string getName() const { return name_; }
    void subscribe(std::string s) { EventRegistry::registerObserver(s, this); }
    void unsubscribe(std::string s) { EventRegistry::deregisterObserver(s, this); }
    void handleMessage(std::string);
private:
    string name_;
};

class Subject {
public:
    Subject(const string& name) : name_(name) {}
    string getName() const { return name_; }
    void generateMessage() {
        cout << name_ << " sent a message" << endl;
        EventRegistry::handleMessage(this->getName());
    }
private:
    string name_;
};

void EventRegistry::registerObserver(std::string s, Observer* o) {
    observerMap_[s].insert(o);
    cout << o->getName() << " subscribed to " << s << endl;
}

void EventRegistry::deregisterObserver(std::string s, Observer* o) {
    observerMap_[s].erase(o);
    cout << o->getName() << " unsubscribed from " << s << endl;
}

void EventRegistry::handleMessage(std::string s) {
    for (auto e : observerMap_[s])
        e->handleMessage(s);
}

void Observer::handleMessage(std::string s) {
    cout << name_ << " received message from " << s << endl;
}


int main() {
    Subject  sue("Subject Sue"), steve("Subject Steve");
    Observer olaf("Observer Olaf"), olga("Observer Olga");


    olaf.subscribe("sue"); olaf.subscribe("steve");
    olga.subscribe("sue");

    cout << endl;



    sue.generateMessage();
    steve.generateMessage();
    cout << endl;


    olga.unsubscribe("sue");
    sue.generateMessage();
}