#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable
{
private:
    struct Entry
    {
        int key;
        int value;
        bool is_deleted;

        Entry() {key = 0, value = 0, is_deleted = false;} // default constructor
        Entry(int key, int value) {is_deleted = false;} // constructor w initializing
    };

    vector<Entry> table; // HT as a vector of Entry objects
    int curr_size;
    int capacity;
    double alpha = 0.8; // load factor
public:

};