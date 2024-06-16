// Nicholas A Moore
// CSIII
// Lab 6
// Part III - Apple Sorting


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <utility>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples {
    double weight; // oz
    string color;  // red or green
    void print() const { cout << color << ", " << weight << endl; }
};



int main() {
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    cout << "Input crate size: ";
    int size = 5.;
    cin >> size;

    vector <Apples> crate(size);

    // function lambda for generate func
    auto freshApple = [&] {Apples temp; temp.weight = minWeight +
        static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
    temp.color = rand() % 2 == 1 ? "green" : "red"; return temp; };

    std::generate(crate.begin(), crate.end(), freshApple);


    // for_each() possibly
    cout << "all apples" << endl;
    std::for_each(crate.begin(), crate.end(), [](Apples i) { i.print(); });


    cout << "Enter weight to find: ";
    double toFind = 5.;
    cin >> toFind;

    // count_if()
   // int cnt = 0;
    auto greaterWeight = [&](Apples i) { if (i.weight > toFind) return true; else return false; };
    auto cnt = std::count_if(crate.begin(), crate.end(), greaterWeight);
 

    cout << "There are " << cnt << " apples heavier than "
        << toFind << " oz" << endl;

    // find_if()

    auto it = std::find_if(crate.begin(), crate.end(), [&](Apples i) { return i.weight > toFind; });
    if (it != crate.end()) {
        cout << "at positions ";
        do {
            cout << it - crate.begin() << " ";
            it = find_if(++it, crate.end(), [&](Apples i) { return i.weight > toFind; });
        } while (it != crate.end());
    }
    else {
        cout << "There are none to be found" << endl;
    }

    cout << endl;


    // max_element()
    auto heaviest = std::max_element(crate.begin(), crate.end(), [](Apples i, Apples j) { return i.weight < j.weight; });
    cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


    // for_each() or accumulate()
    auto accumCallback = [](double accumulator, Apples i) { return accumulator + i.weight; };
    auto sum = std::accumulate(crate.begin(), crate.end(), 0., accumCallback);
    cout << "Total apple weight is: " << sum << " oz" << endl;


    // transform();
    cout << "How much should they grow: ";
    double toGrow = 1.;
    cin >> toGrow;
    auto appleGrowth = [&](Apples& i) { Apples grownApple; grownApple.weight = i.weight + toGrow; grownApple.color = i.color; return grownApple; };
    std::transform(crate.begin(), crate.end(), crate.begin(), appleGrowth);


    // remove_if()
    cout << "Input minimum acceptable weight: ";
    double minAccept = 6.;
    cin >> minAccept;


    // removing small apples
    // nested loops, replace with a single loop modification idiom
    for (auto removed = crate.begin(); removed != crate.end();) {
        if (removed->weight < minAccept) {
            removed = crate.erase(std::remove_if(crate.begin(), crate.end(), [&](Apples i) { if (i.weight < minAccept) return true; else return false; }), crate.end());
        }
        else {
            ++removed;
        }
    }
    cout << "removed " << size - crate.size() << " elements" << endl;


    // bubble sort, replace with sort()
    std::sort(crate.begin(), crate.end(), [](Apples i, Apples j) { return j.weight < i.weight; });

    // for_each() possibly
    cout << "sorted remaining apples" << endl;
    std::for_each(crate.begin(), crate.end(), [](Apples i) { i.print(); });

}
