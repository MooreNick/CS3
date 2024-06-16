// Nicholas A Moore
// CSIII Lab 10 Part III
// 04/05/2023

#include "StateTransition.hpp"
#include <ctime>
#include <queue>

int main() {
	//srand(2);
	srand(time(nullptr));


	std::queue<Process> readyQueue, blockedQueue;
	Process p;
	readyQueue.push(p);


	std::cout << "Here are our process:" << std::endl;
	std::cout << "PID " << p.getID() << ' ' << p.report() << std::endl;

	for (int i = 0; i < 4; ++i) { // clone 4 new process
		auto temp = p.clone();
		std::cout << "PID " << temp->getID() << ' ' << temp->report() << std::endl;
		readyQueue.push(*temp);
	}

	std::cout << "Scheduling will begin" << std::endl;

	readyQueue.front().dispatch();

	std::cout << "PID " << readyQueue.front().getID() << ' ' << readyQueue.front().report() << std::endl;

	while (readyQueue.size() != 0 || blockedQueue.size() != 0) {

		if (!readyQueue.empty()) {

			int nextStep = rand() % 3; // 33% chance for front() to exit, suspend, or block

			if (nextStep == 0) { // exit (destroy)
				std::cout << "Exiting..." << std::endl;
				auto hold = readyQueue.front(); // get front item
				hold.exit(); // change state
				readyQueue.pop(); // remove it

				std::cout << "PID " << hold.getID() << ' ' << hold.report() << std::endl;

					if (!readyQueue.empty()) { // make sure it wasn't last
						readyQueue.front().dispatch();
						std::cout << "PID " << readyQueue.front().getID() << ' ' << readyQueue.front().report() << std::endl;
					}
			}


			if (nextStep == 1) { // suspend (ready)
				std::cout << "Suspending..." << std::endl;
				readyQueue.front().suspend();
				auto hold = readyQueue.front(); // get front
				readyQueue.pop(); // remove it
				readyQueue.push(hold); // put it back at end
				readyQueue.front().dispatch(); // new front should be running

				std::cout << "PID " << hold.getID() << ' ' << hold.report() << std::endl;
				std::cout << "PID " << readyQueue.front().getID() << ' ' << readyQueue.front().report() << std::endl;
			}

			if (nextStep == 2) { // block (blocked)
				std::cout << "Blocking..." << std::endl;
				readyQueue.front().block(); 
				auto hold = readyQueue.front(); // get front
				readyQueue.pop(); // remove it 
				blockedQueue.push(hold); // added to block queue

				std::cout << "PID " << hold.getID() << ' ' << hold.report() << std::endl;

					if (!readyQueue.empty()) { // make sure it wasn't last
						readyQueue.front().dispatch();
						std::cout << "PID " << readyQueue.front().getID() << ' ' << readyQueue.front().report() << std::endl;
					}
			}
		}


		if (!blockedQueue.empty()) {

			int blockedNextStep = rand() % 3;

			if (blockedNextStep == 0) { // 33% chance of being unblocked
				std::cout << "Unblocking..." << std::endl;
				auto hold = blockedQueue.front(); // get front item
				blockedQueue.pop(); // remove it
				hold.unblock(); // ready
				readyQueue.push(hold); // put it in readyQueue

				std::cout << "PID " << hold.getID() << ' ' << hold.report() << std::endl;

					if (readyQueue.size() == 1) { // newly pushed blocked process is ONLY process in ready
						readyQueue.front().dispatch();
						std::cout << "PID " << readyQueue.front().getID() << " is now the only process in the Ready Queue" << std::endl;
						std::cout << "PID " << readyQueue.front().getID() << ' ' << readyQueue.front().report() << std::endl;
					}

			}
		}

		std::cout << std::endl;
	}

	std::cout << "Scheduler is finished" << std::endl;
}