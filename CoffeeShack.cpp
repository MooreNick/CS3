// Nicholas A Moore
// 04/07/2023
// Lab 11

#include "CoffeeShack.hpp"
#include <iostream>
#include <vector>

using std::cout; using std::endl; using std::cin;

int main() {

	int MAX_CUSTOMERS = 4; // Lab Requirements
	int CURRENT_CUSTOMER = 0; // Starting position
	char size = 'x'; // initializer
	char ingredient = 'x'; // initializer

	Barista* employee = new JuniorBarista(new SeniorBarista(new Manager)); // chain of responsibility initialization

	while (CURRENT_CUSTOMER != MAX_CUSTOMERS) {
		srand(time(nullptr)); // rand seed


		Drink* currOrder;
		std::cout << "Welcome to the Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee?" << endl;
		std::cin >> size; // get desired size

		if (size == 'l') {
			currOrder = new Drink(DrinkType::large, 10);
		}

		else if (size == 'm') {
			currOrder = new Drink(DrinkType::medium, 7);
		}

		else if (size == 's') {
			currOrder = new Drink(DrinkType::small, 5);
		}

		else { // fail save
			currOrder = new Drink(DrinkType::small, 5);
		}

		while (ingredient != 'd') {
			cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?" << endl;
			cin >> ingredient;
			currOrder = employee->handleRequest(currOrder, ingredient); // chain of resp : Junior can serve drink, senior adds sugar/cream, manager adds honey
		}


		std::string custName;
		cout << "What is your name?" << endl;
		cin >> custName;

	
		employee->newCustomer(new Customer(custName, employee, currOrder)); // registered with Barista
		

		int randomChance = rand() % 2; // chance order is finished
		if (randomChance == 0) {
			auto it = employee->allOrders_.begin(); // first order is finished
			employee->notifyCustomers();
			employee->servedCustomer(*it);
		}

		++CURRENT_CUSTOMER;

		if (CURRENT_CUSTOMER == MAX_CUSTOMERS) {

			while (!employee->everyoneServed()) { // everyone ordered, must serve all
				auto it = employee->allOrders_.begin();
				employee->notifyCustomers(); // notification to all
				employee->servedCustomer(*it); // specific price/name for finished drink
			}
		}


		// reset
		ingredient = 'x';
		size = 'x';
		custName = "";

	}


	return 0;




	// Main from part 1 if it is still needed
	/*
	Drink *order;

	char size;
	cout << "Welcome to the Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee?" << endl;
	cin >> size;

	if (size == 'l') {
		order = new Drink(DrinkType::large, 10);
	}

	else if (size == 'm') {
		order = new Drink(DrinkType::medium, 7);
	}

	else if (size == 's') {
		order = new Drink(DrinkType::small, 5);
	}

	else {
		order = new Drink(DrinkType::small, 5);
	}
	
	char ingredient = 'x';
	while (ingredient != 'd') {
		cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?" << endl;
		cin >> ingredient;

		if (ingredient == 's') {
			order = new Sugar(order);
		}
		
		else if (ingredient == 'c') {
			order = new Cream(order);
		}

		else if (ingredient == 'h') {
			order = new Honey(order);
		}

		else {
			ingredient = 'd';
		}
	}
	std::string custName;
	cout << "What is your name?" << endl;
	cin >> custName;

	cout << custName << ", your " << order->getName() << " is ready, it costs " << order->getPrice() << "dollars." << endl;
	*/

}
