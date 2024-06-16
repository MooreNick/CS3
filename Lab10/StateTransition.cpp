#include "StateTransition.hpp"

int main() {
	Process p;
	Process p2;
	Process p3;

	std:: cout << p.report();
	p2.report();
	p3.report();

	p.dispatch();
	std::cout << p.report();

	p.block();
	std::cout << p.report();

	p.unblock();
	std::cout << p.report();

	p.dispatch();
	std::cout << p.report();

	p.suspend();
	std::cout << p.report();

	p.dispatch();
	std::cout << p.report();

	return 0;
	
//	p.exit();

}