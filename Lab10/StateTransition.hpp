#ifndef CS3_LAB10_PART2_
#define CS3_LAB10_PART2_

// Nicholas A Moore
// CSIII
// Lab 10 Part II
// 04/05/2023

#include <string>
#include <iostream>

class State;

class Ready;

class Process {
public:
	Process();

	void dispatch();
	void block();
	void unblock();
	void suspend();
	void exit();

	Process* clone() { Process* clone = new Process; return clone; }; // for part 3

	int getID() { return id_; }

	std::string report();

	void changeState(State* s) {
		state_ = s;
	}

private:
	State* state_;
	int id_;
	static int nextID_;
};

class State {
public:
	virtual void dispatch(Process*) {};
	virtual void block(Process*) {};
	virtual void unblock(Process*) {};
	virtual void suspend(Process*) {};
	virtual void exit(Process*) {};

	virtual std::string report() = 0;

	void changeState(Process* p, State* s) {
		p->changeState(s);
	}
};

class Ready : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}

	std::string report() override { return "Ready"; }
	void dispatch(Process*) override;

private:
	Ready() {};
	Ready& operator=(const Ready&) {};
	Ready(const Ready&) = delete;
};

class Running : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Running;
		return onlyInstance;
	}

	std::string report() override { return "Running"; }
	void block(Process*) override;
	void suspend(Process*) override;
	void exit(Process*) override;
private:
	Running() {};
	Running& operator=(const Running&) {};
	Running(const Running&) = delete;

};

class Blocked : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Blocked;
		return onlyInstance;
	}

	std::string report() override { return "Blocked"; }
	void unblock(Process*) override;
private:
	Blocked() {};
	Blocked& operator=(const Blocked&) {};
	Blocked(const Blocked&) = delete;
};

class Destroyed : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Destroyed;
		return onlyInstance;
	}

	std::string report() override { return "Destroyed"; }
};


void Ready::dispatch(Process* p) {
	changeState(p, Running::instance());
};

void Running::block(Process* p) {
	changeState(p, Blocked::instance());
};

void Running::suspend(Process* p) {
	changeState(p, Ready::instance());
}

void Running::exit(Process* p) {
	changeState(p, Destroyed::instance());
}

void Blocked::unblock(Process* p) {
	changeState(p, Ready::instance());
}

int Process::nextID_ = 0;
Process::Process() {
	//	nextID_ = 0;
	id_ = nextID_;
	++nextID_;
	state_ = Ready::instance();
}

std::string Process::report() {
	return state_->report();
}

void Process::dispatch() {
	state_->dispatch(this);
}

void Process::block() {
	state_->block(this);
}

void Process::unblock() {
	state_->unblock(this);
}

void Process::suspend() {
	state_->suspend(this);
}

void Process::exit() {
	state_->exit(this);
}
#endif