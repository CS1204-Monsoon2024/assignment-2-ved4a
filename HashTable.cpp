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

    int next_prime(int num) {
        if (num <= 2) return 2;
        if (num % 2 == 0) num++;  // make sure n is odd
        while (!is_prime(num)) {
            num += 2; // increment odd numbers
        }
        return num;
    };

    void resize_table() {
        int old_capacity = capacity;
        capacity = next_prime(2 * old_capacity); // to 2x the old capacity + ensure its prime

        vector<Entry> old_table = table;

        table.clear(); // delete contents to allow rehashing
        table.resize(capacity); // new table made
        curr_size = 0;

        for (int i = 0; i < old_capacity; i++) {
            if (old_table[i].key != 0 && !old_table[i].is_deleted) {
                insert(old_table[i].key, old_table[i].value); // need to code up insert
            }
        }
    };

    int probe(int key, int i)
    {
        return (hash(key) + (i * i)) % capacity;
    };

public:
    HashTable(int size)
    {
        capacity = next_prime(size); // if size is alr prime nothing changes
        table.resize(capacity);
        curr_size = 0;
    };

bool insert(int value) {
    int key = hash(value); // find key

    if ((double)curr_size / capacity >= alpha) { // check if we need to resize
        resize_table();  // resize if load factor exceeds threshold
    }

    int i = 0;
    while (i < capacity) {
        int newIndex = probe(key, i);  // probe for the correct position
        if (table[newIndex].key == 0 || table[newIndex].is_deleted) {
            table[newIndex] = Entry(key, value);
            curr_size++;
            return true;
        }
        i++;
    }
    return false;  // if unable to insert
}


};