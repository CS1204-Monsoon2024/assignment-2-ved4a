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

    int hash(int key)
    {
        return key % capacity;
    };

    bool is_prime(int num)
    {
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        for (int i = 3; i * i <= num; i += 2) { // until sqrt num
            if (num % i == 0) return false;
        }
        return true;
    };

public:

};