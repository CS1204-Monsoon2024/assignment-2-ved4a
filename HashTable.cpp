#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    struct Entry {
        int key;     // Key that is hashed
        int value;   // Data (or value) stored in the hash table
        bool is_deleted;

        Entry() { key = 0; value = 0; is_deleted = false; }
        Entry(int key, int value) : key(key), value(value), is_deleted(false) {}
    };

    vector<Entry> table;
    int curr_size;
    int capacity;
    double alpha = 0.8; // load factor

    // Hash function to determine index based on key
    int hash(int key) {
        return key % capacity;
    }

    bool is_prime(int num) {
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        for (int i = 3; i * i <= num; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int next_prime(int num) {
        if (num <= 2) return 2;
        if (num % 2 == 0) num++;
        while (!is_prime(num)) {
            num += 2;
        }
        return num;
    }

    void resize_table() {
        int old_capacity = capacity;
        capacity = next_prime(2 * old_capacity);

        vector<Entry> old_table = table;
        table.clear();
        table.resize(capacity);
        curr_size = 0;

        // Rehashing all old entries
        for (int i = 0; i < old_capacity; i++) {
            if (old_table[i].key != 0 && !old_table[i].is_deleted) {
                insert(old_table[i].key, old_table[i].value);  // Reinsert with original key-value
            }
        }
    }

    int probe(int key, int i) {
        return (hash(key) + (i * i)) % capacity;
    }

public:
    HashTable(int size) {
        capacity = next_prime(size);
        table.resize(capacity);
        curr_size = 0;
    }

    // Insert using a distinct key and value
    bool insert(int key, int value) {
        if ((double)curr_size / capacity >= alpha) {
            resize_table();
        }

        int i = 0;
        while (i < capacity) {
            int newIndex = probe(key, i);
            if (table[newIndex].key == 0 || table[newIndex].is_deleted) {
                table[newIndex] = Entry(key, value);
                curr_size++;
                return true;
            }
            i++;
        }
        return false;
    }

    // Search for a value using its key
    int search(int key) {
        int i = 0;
        while (i < capacity) {
            int index = probe(key, i);
            if (table[index].key == key && !table[index].is_deleted) {
                return table[index].value;
            }
            if (table[index].key == 0 && !table[index].is_deleted) {
                return -1;  // Key not found
            }
            i++;
        }
        return -1;
    }

    bool remove(int key) {
        int i = 0;
        while (i < capacity) {
            int index = probe(key, i);
            if (table[index].key == key && !table[index].is_deleted) {
                table[index].is_deleted = true;
                curr_size--;
                return true;
            }
            if (table[index].key == 0 && !table[index].is_deleted) {
                return false;  // Key not found
            }
            i++;
        }
        return false;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].key != 0 && !table[i].is_deleted) {
                cout << table[i].value << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};
