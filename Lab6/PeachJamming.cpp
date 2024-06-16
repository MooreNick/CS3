// Nicholas A Moore
// CSIII
// Lab 6
// Part IV


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Peaches {
    double weight; // oz
    bool ripe;  // ripe or not
    void print() const { cout << (ripe ? "ripe" : "green") << ", " << weight << endl; }
};

class weightFunctor {
public:
    weightFunctor(double max) : max_(max) {}
    double operator() (double max) { return max_; }
    double getMax() { return max_; }
private:
    double max_;
};

int main() {
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;


    cout << "Input basket size: ";
    int size;
    cin >> size;

    vector <Peaches> basket(size);

    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    auto newPeach = [&]() { Peaches temp; temp.ripe = rand() & 2; temp.weight = minWeight +
        static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight); return temp; };
    std::generate(basket.begin(), basket.end(), newPeach);


    // for_each() possibly
    cout << "all peaches" << endl;
    std::for_each(basket.begin(), basket.end(), [](Peaches i) { i.print(); });


    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Peaches> peck;
    std::remove_copy_if(basket.begin(), basket.end(), std::front_inserter(peck), [](Peaches i) { return !i.ripe; });
    basket.erase(std::remove_if(basket.begin(), basket.end(), [](Peaches i) { return i.ripe; }),basket.end());



    // for_each() possibly
    cout << "peaches remainng in the basket" << endl;
    std::for_each(basket.begin(), basket.end(), [](Peaches i) { i.print(); });
    cout << endl;

    // for_each() possibly
    cout << "peaches moved to the peck" << endl;
    std::for_each(peck.begin(), peck.end(), [](Peaches i) {i.print(); });


    // prints every "space" peach in the peck
    const int space = 3;
    cout << "\nevery " << space << "\'d peach in the peck" << endl;

    // replace with advance()/next()/distance()
    // no explicit iterator arithmetic

    auto printer = peck.cbegin();
    auto bounds = peck.cend();
    while (printer != bounds) {
        if (bounds - printer > space) {
            std::advance(printer, space);
            printer->print();
        }
        else {
            ++printer;
        }
    }


    // putting all small ripe peaches in a jam
    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()
    const double weightToJam = 10.0;
    double jamWeight = 0;
    using namespace std::placeholders;

    weightFunctor configWeight(weightToJam);
    auto weight = std::bind(configWeight, weightToJam);

    auto comparison = [&](Peaches i) { if (i.weight < weight()) { jamWeight += i.weight; return true; } else return false; };

    std::count_if(peck.begin(), peck.end(), comparison);
    peck.erase(std::remove_if(peck.begin(), peck.end(), [&](Peaches i) { if (i.weight < weight()) { return true; } else { return false; } }), peck.end());

    cout << "Weight of jam is: " << jamWeight << endl;

}
