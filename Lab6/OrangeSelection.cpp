// Nicholas A Moore
// CSIII
// Lab 6
// Part II - Orange Selection


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
    Variety v;
    string color; // red, green or orange
};

/*
int main() {
    srand(time(nullptr));
    vector <Fruit> tree(rand() % 100 + 1);

    std::multimap<Variety, string> fruitTree;

    for (int i = 0; i < rand() % 100 + 1; ++i) {
        fruitTree.emplace(std::make_pair(static_cast<Variety>(rand() % 3), colors[rand() % 3]));
    }

    cout << "Colors of the oranges: ";
    for (auto it = fruitTree.lower_bound(Variety::orange); it != fruitTree.upper_bound(Variety::orange); ++it) {
        cout << it->second << ' ';
    }
    cout << endl;
}
*/