// Nicholas A Moore
// CS3 Lab 10 Part II
// 04/05/2023

// This file shows the StateTransition.hpp implementation works as expected
// ENDING COMMENT AT END OF MAIN

/*

#include "StateTransition.hpp"

using std::cout;
using std::endl;

int main() {
	Process p;
	Process p2;

	cout << "We have two processes: " << p.getID() << " has status of " << p.report() << endl
		<< " and " << p2.getID() << " has status of " << p2.report() << endl;

	cout << "We will dispatch 0 and and attempt to unblock 1" << endl;

	p.dispatch();
	p2.unblock();

	cout << "Their new status" << endl << p.getID() << " has status of " << p.report() << endl
		<< p2.getID() << " has status of " << p2.report() << endl;

	cout << "Now we will block our running process and dispatch our ready process and then suspend it" << endl;
	p.block();
	p2.dispatch();
	p2.suspend();

	cout << "Their new status" << endl << p.getID() << " has status of " << p.report() << endl
		<< p2.getID() << " has status of " << p2.report() << endl;

	cout << "Now we will unblock our blocked process and dispatch both" << endl;

	p.unblock();
	p.dispatch();
	p2.dispatch();

	cout << "Their new status" << endl << p.getID() << " has status of " << p.report() << endl
		<< p2.getID() << " has status of " << p2.report() << endl;

	cout << "Now we will destroy both" << endl;

	p.exit();
	p2.exit();

	cout << "Their new status" << endl << p.getID() << " has status of " << p.report() << endl
		<< p2.getID() << " has status of " << p2.report() << endl;

	

	return 0;


}
*/