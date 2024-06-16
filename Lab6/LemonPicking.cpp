// Nicholas A Moore
// CSIII
// Lab 6
// Part I - Lemon Picking


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;



struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

/*
int main() {
    srand(time(nullptr));
  //  vector <Lemon> box(rand() % maxBoxSize + 1); // random box size
    std::priority_queue<Lemon> lemonBox;


    int boxSize = rand() % maxBoxSize + 1;
    for (int i = 0; i < boxSize; ++i) {
        Lemon temp;
        temp.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
        lemonBox.push(temp);
    }

    while (!lemonBox.empty()) {
        cout << lemonBox.top().quality << " ";
        lemonBox.pop();
    }

    cout << endl;

}
*/