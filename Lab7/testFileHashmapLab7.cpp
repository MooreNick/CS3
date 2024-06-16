// Nicholas A Moore
// CSIII
// Lab 7
// Updating Hash Container
// 03/03/2023

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

// template tests hashmap inserts
template <typename Key, typename Value>
void test_insert(hashmap<Key, Value>& hm, Key key, Value value) {
    cout << "[*] Inserting " << key << ": " << value << "...\n";
    pair<const pair<const Key, Value>*, bool> result = hm.insert(make_pair(key, value));

    if (result.second)
        cout << "--> Done!\n";
    else
        cout << "--> Failed! Key " << result.first->first
        << " already exists with value " << result.first->second << endl;
}

// template tests hashmap erases
template <typename Key, typename Value>
void test_erase(hashmap<Key, Value>& hm, Key key) {
    cout << "[*] Erasing " << key << "...\n";
    pair<const pair<const Key, Value>*, bool> result = hm.erase(key);

    if (result.second) {
        cout << "--> Done! ";
        if (result.first)
            cout << "The next element is " << result.first->first
            << ": " << result.first->second << endl;
        else
            cout << "There is no next element\n";
    }
    else {
        cout << "--> Failed! Key " << key << " doesn't exist!\n";
    }
}


int main() {

    cout << "Test file for Lab 7 Hashmap" << endl << endl;

    cout << "Creating and filling an <int, int> Hashmap" << endl;

    hashmap<int, int> myMap;
    
    test_insert(myMap, 1, 10);
    test_insert(myMap, 2, 20);
    test_insert(myMap, 1, 100);
    test_insert(myMap, 3, 107);

    cout << "testing erase" << endl;

    test_erase(myMap, 1);
    test_erase(myMap, 2);
    test_erase(myMap, 3);

    cout << "testing rehash" << endl;
    cout << "before rehash" << "Number of Buckets: " << myMap.getBuckets() << endl;
    myMap.rehash(205);
    cout << "after rehash (rehash invoked with 205)" << "Number of Buckets: " << myMap.getBuckets() << endl;
    




    return 0;
}