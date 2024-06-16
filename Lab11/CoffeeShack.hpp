#ifndef CS3_LAB11_
#define CS3_LAB11_

// Nicholas A Moore
// 04/07/2023
// Lab 11


#include <string>
#include <unordered_set>
#include <iostream>
#include <ctime>

enum class DrinkType { small, medium, large };

class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {}
    virtual int getPrice() const { return price_; };
    virtual std::string getName() const {
        if (type_ == DrinkType::small) return "Small ";
        if (type_ == DrinkType::medium) return "Medium ";
        if (type_ == DrinkType::large) return "Large ";
        else return "error";
    };
private:
    int price_;
    DrinkType type_;
};

class Sugar : public Drink {
public:
    Sugar(Drink* wrapped) : wrapped_(wrapped) {};
    int getPrice() const override {
        return wrapped_->getPrice() + 1;
    }
    std::string getName() const override {
        return wrapped_->getName() + "Sugar ";
    }
private:
    Drink* wrapped_;
};

class Cream : public Drink {
public:
    Cream(Drink* wrapped) : wrapped_(wrapped) {};
    int getPrice() const override {
        return wrapped_->getPrice() + 2; // Cream is 2 dolalrs
    }
    std::string getName() const override {
        return wrapped_->getName() + "Cream ";
    }
private:
    Drink* wrapped_;

};

class Honey : public Drink {
public:
    Honey(Drink* wrapped) : wrapped_(wrapped) {};
    int getPrice() const override {
        return wrapped_->getPrice() + 3; // Honey is 3 dollars
    }
    std::string getName() const override {
        return wrapped_->getName() + "Honey ";
    }
private:
    Drink* wrapped_;
};

// Chain of Responsibility and Observer Patterns

class Customer; // forward delcaration for observer funcs

class Barista {
public:
    Barista(Barista* successor = nullptr) : successor_(successor) {};

    virtual Drink* handleRequest(Drink* order, char ingredient) {
        if (successor_ != nullptr) {
            return successor_->handleRequest(order, ingredient);
        }
        else {
            return new Drink; // fail save
        }
    }


    void newCustomer(Customer* c) { allOrders_.insert(c); } // Register
    void servedCustomer(Customer* c); // outside def



    bool everyoneServed() { return allOrders_.empty(); }

    void notifyCustomers() const;

    std::unordered_set<Customer*> allOrders_; // each customer registered

private:
    Barista* successor_;

};

class Customer {
public:
    Customer(std::string name, Barista* barista, Drink* order) : name_(name), barista_(barista), order_(order) {
        barista_->newCustomer(this); // register 
    };

    void notify() {
        std::cout << "Customer " << name_ << " reports order is finished" << std::endl;
    }

    //incase they are needed
    std::string getName() const { return name_; }
    Barista* getBarista() const { return barista_; }
    Drink* getOrder() const { return order_; }

private:
    std::string name_;
    Barista* barista_;
    Drink* order_;
};

class JuniorBarista : public Barista {
public:
    JuniorBarista(Barista* successor = nullptr) : Barista(successor) {};

    Drink* handleRequest(Drink* order, char ingredient) override {
        if (ingredient == 'd') {
            std::cout << "Junior Barista handled your order with no additional ingredients" << std::endl;
            return order;
        }
        else {
            return Barista::handleRequest(order, ingredient);
        }
    }
};

class SeniorBarista : public Barista {
public:
    SeniorBarista(Barista* successor = nullptr) : Barista(successor) {};

    Drink* handleRequest(Drink* order, char ingredient) override {
        if (ingredient == 's') {
                std::cout << "Senior Barista added sugar" << std::endl;
                order = new Sugar(order);
                return order;
        }
        else if (ingredient == 'c') {
                std::cout << "Senior Barista added cream" << std::endl;
                order = new Cream(order);
                return order;
        }
        else {
             return Barista::handleRequest(order, ingredient);
        }
    }
};

class Manager : public Barista {
public:
    Manager(Barista* successor = nullptr) : Barista(successor) {};

    Drink* handleRequest(Drink* order, char ingredient) override {
        if (ingredient == 'h') {
            std::cout << "Manager added honey" << std::endl;
            order = new Honey(order);
            return order;
        }
        else {
            return Barista::handleRequest(order, ingredient);
        }
    }
};


void Barista::servedCustomer(Customer* c) {
    // gives specific drink info and erases
    std::cout << c->getOrder()->getName() << " your order is ready and costs " << c->getOrder()->getPrice() << " dollars." << std::endl;
    allOrders_.erase(c);
}


void Barista::notifyCustomers() const { // notify everyone a drink has been finished
        for (auto& e : allOrders_) {
            e->notify();
        }
}

#endif