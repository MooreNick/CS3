// Nicholas A Moore
// CSIII
// Lab 9 Part I
// 03/17/2023

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
    CarLot();
    Car* testDriveCar() { return car4sale_; }

    // if a car is bought, requests a new one
    Car* buyCar(int i) {
        Car* bought = allCars4sale_[i];
        allCars4sale_[i] =
            factories_[rand() % factories_.size()]->requestCar();
        return bought;
    }

    int lotSize() const { return lotSize_; }

    Car* nextCar(int i) { return allCars4sale_[i]; }

private:
    Car* car4sale_; // single car for sale at the lot
    vector<Car*> allCars4sale_;
    vector<CarFactory*> factories_;
    const int lotSize_ = 8;
};


CarLot::CarLot() {
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    for (int i = 0; i < lotSize_; ++i) { // get all 8 cars for lot
        car4sale_ = factories_[rand() % factories_.size()]->requestCar();
        allCars4sale_.push_back(car4sale_);
    }
}



CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    std::string models[5] = { "Corolla", "Camry", "Prius", "4Runner", "Yaris" };
    std::string prefModel = models[rand() % 5];

    for (int i = 0; i < carLotPtr->lotSize(); ++i) {

        Car* toBuy = carLotPtr->nextCar(i);

        cout << "Jill Toyoter" << id << endl;
        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();

        if (toBuy->getMake() == "Toyota" && toBuy->getModel() == prefModel) {
            cout << " love it! buying it!" << endl;
            carLotPtr->buyCar(i);
        }
        else
            cout << " did not like it!" << endl;
    }
}

// test-drives a car
// buys it if Ford
void fordLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    std::string models[4] = { "Focus", "Mustang", "Explorer", "F-150" };
    std::string prefModel = models[rand() % 4];


    for (int i = 0; i < carLotPtr->lotSize(); ++i) {

        Car* toBuy = carLotPtr->nextCar(i);

        cout << "Jack Fordman " << id << endl;
        cout << " test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();

        if (toBuy->getMake() == "Ford" && toBuy->getModel() == prefModel) {
            cout << " love it! buying it!" << endl;
            carLotPtr->buyCar(i);
        }
        else
            cout << " did not like it!" << endl;
    }
}


/*
int main() {
    srand(time(nullptr));

    const int numBuyers = 20;
    for (int i = 0; i < numBuyers; ++i)
        if (rand() % 2 == 0)
            toyotaLover(i);
        else
            fordLover(i);

}*/