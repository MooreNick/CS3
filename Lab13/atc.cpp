// Nicholas A Moore
// CSIII
// Lab 13 Part I
// 04/21/2023

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>
#include <cctype>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;

enum class logos {AirFrance, KLM, AeroFlot, Lufthansa, Delta, United, JetBlue};

// abstract flyweight
class Logo {
public:
	virtual std::string logo() = 0;
};

// concrete flyweights
class AirFrance : public Logo {
public:
	std::string logo() override { return "AIRFRANCE"; }
};

class KLM : public Logo {
public:
	std::string logo() override { return "KLM"; }
};

class AeroFlot : public Logo {
public:
	std::string logo() override { return "AEROFLOT"; }
};

class Lufthansa : public Logo {
public:
	std::string logo() override { return "LUFTHANSA"; }
};

class Delta : public Logo {
public:
	std::string logo() override { return "DELTA"; }
};

class United : public Logo {
public:
	std::string logo() override { return "UNITED"; }
};

class JetBlue : public Logo {
public:
	std::string logo() override { return "JETBLUE"; }
};

class LogoPrinter {
public:
	static Logo* logoPicker(logos l) {
		if (logos_.find(l) == logos_.end()) { // not present
			switch (l) {
				case logos::AirFrance:
					logos_[l] = new AirFrance;
					break;
				case logos::KLM:
					logos_[l] = new KLM;
					break;
				case logos::AeroFlot:
					logos_[l] = new AeroFlot;
					break;
				case logos::Lufthansa:
					logos_[l] = new Lufthansa;
					break;
				case logos::Delta:
					logos_[l] = new Delta;
					break;
				case logos::United:
					logos_[l] = new United;
					break;
				case logos::JetBlue:
					logos_[l] = new JetBlue;
					break;
			}
		}
		return logos_[l];
	}
private:
	static std::map<logos, Logo*> logos_;
};
std::map<logos, Logo*> LogoPrinter::logos_; // initialize static

// abstract mediator
class Controller {
public:
	virtual void join(class Flight*) = 0;
	virtual void leave(class Flight*) = 0;
	virtual void broadcast() = 0;
	virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower : public Controller {
public:
	void join(class Flight*) override;
	void leave(class Flight*) override;
	void broadcast() override;
	void observe() override;
private:
	std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
	Flight(Controller* controller) :controller_(controller), status_(Status::waiting) {
		task_ = rand() % 2 ? Task::taxiing : Task::approaching;
		controller_->join(this);
	}
	void receive(const string& msg) {
		if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos) {
			if (msg.find("clear") != string::npos) {
				cout << flightNo_ << " roger that, ";
				cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
				status_ = Status::cleared;
			}
			else if (msg.find("status") != string::npos) {
				cout << flightNo_
					<< (status_ == Status::waiting ? " waiting to " : " cleared to ")
					<< (task_ == Task::taxiing ? "take off" : "land") << endl;
			}
			else
				cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
		}
	}
	bool isCleared() const { return status_ == Status::cleared; }
	void proceed() {
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // wait a while    
		cout << flightNo_
			<< (task_ == Task::taxiing ? " took off" : " landed")
			<< ". Have a good day!" << endl;

		cout << "..." << logo_->logo() << getNumber() << (task_ == Task::taxiing ? " took off" : " landed") << "..." << std::endl;

		controller_->leave(this);
	}

	std::string getNumber() {
		std::string result = "";
		for (int i = 0; i < flightNo_.size(); ++i) {
			if (isdigit(flightNo_[i]))
				result += flightNo_[i];
		}
		return result;
	}

protected:
	string flightNo_;
	Controller* controller_;
	Logo* logo_;
	enum class Task { taxiing, approaching };  Task task_;
	enum class Status { waiting, cleared };    Status status_;
};

// concrete colleagues
class Airbus : public Flight {
public:
	Airbus(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "AirFrance", "KLM", "Aeroflot", "Lufthansa" };
//		int companyPick = rand() % companies.size();
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);

		if (flightNo_.find("AirFrance") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::AirFrance);

		if (flightNo_.find("KLM") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::KLM);

		if (flightNo_.find("AeroFlot") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::AeroFlot);

		if (flightNo_.find("Lufthansa") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::Lufthansa);

		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};

class Boeing : public Flight {
public:
	Boeing(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "Delta", "United", "JetBlue" };
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);

		if (flightNo_.find("Delta") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::Delta);

		if (flightNo_.find("United") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::United);

		if (flightNo_.find("JetBlue") != std::string::npos)
			logo_ = LogoPrinter::logoPicker(logos::JetBlue);

		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};


// member functions for Tower
void Tower::broadcast() {
	cout << "Tower: ";
	string msg;
	getline(cin, msg);
	if (!msg.empty())
		for (auto f : waiting_) f->receive(msg);
}


void Tower::observe() {
	auto findCleared = [](Flight* f) {return f->isCleared(); };

	auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);

	while (toProceed != waiting_.end()) { // found a cleared flight
		(*toProceed)->proceed();
		toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
		if (toProceed != waiting_.end())
			cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
	}
}


void Tower::join(Flight* f) {
	waiting_.insert(f);
}


void Tower::leave(Flight* f) {
	waiting_.erase(f);
	delete f;
}


// ENDING COMMENT BELOW MAIN

/*

int main() {
	srand(time(nullptr));
	Tower jfk;

	new Boeing(&jfk);
	new Airbus(&jfk);
	new Boeing(&jfk);
	new Airbus(&jfk);

	while (true) {
		jfk.broadcast();
		jfk.observe();
		if (rand() % 2) {
			if (rand() % 2)
				new Boeing(&jfk);
			else
				new Airbus(&jfk);
		}
	}
}
*/
