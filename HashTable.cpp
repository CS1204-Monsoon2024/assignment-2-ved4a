#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    struct Entry {
        int value;
        bool is_deleted;

        Entry() { value = 0; is_deleted = false; }
        Entry(int value) : value(value), is_deleted(false) {}
    };

    vector<Entry> table;
    int curr_size;
    int capacity;
    double alpha = 0.8;

    int hash(int value) {
        return value % capacity;
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

        for (int i = 0; i < old_capacity; i++) {
            if (old_table[i].value != 0 && !old_table[i].is_deleted) {
                insert(old_table[i].value);  // Reinsert the old value
            }
        }
    }

    int probe(int value, int i) {
        return (hash(value) + (i * i)) % capacity;
    }

public:
    HashTable(int size) {
        capacity = next_prime(size);
        table.resize(capacity);
        curr_size = 0;
    }

    bool insert(int value) {
        if (search(value) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return false;
        }

        if ((double)curr_size / capacity >= alpha) {
            resize_table();
        }

        int i = 0;
        while (i < capacity) {
            int newIndex = probe(value, i);
            if (table[newIndex].value == 0 || table[newIndex].is_deleted) {
                table[newIndex] = Entry(value);
                curr_size++;
                return true;
            }
            i++;
        }
        cout << "Max probing limit reached!" << endl;
        return false;
    }

    int search(int value) {
        int i = 0;
        while (i < capacity) {
            int index = probe(value, i);
            if (table[index].value == value && !table[index].is_deleted) {
                return index;  // Return the index where the value is found
            }
            if (table[index].value == 0 && !table[index].is_deleted) {
                return -1;  // Value not found
            }
            i++;
        }
        return -1;
    }

    bool remove(int value) {
        int i = 0;
        while (i < capacity) {
            int index = probe(value, i);
            if (table[index].value == value && !table[index].is_deleted) {
                table[index].is_deleted = true;
                curr_size--;
                return true;
            }
            if (table[index].value == 0 && !table[index].is_deleted) {
                cout << "Element not found" << endl;
                return false;  // Value not found
            }
            i++;
        }
        cout << "Element not found" << endl;
        return false;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].value != 0 && !table[i].is_deleted) {
                cout << table[i].value << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};
