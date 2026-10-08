#include "Hashtable.h"
#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <stdexcept>

int Hashtable::hashFunction(int number) const { return number % capacity; }

void Hashtable::resize() {
    if (capacity > std::numeric_limits<int>::max() / 2)
        throw std::overflow_error("Hash table capacity is too large");
    const int newCapacity = capacity * 2;
    std::unique_ptr<int[]> newTable(new int[newCapacity]);
    std::fill(newTable.get(), newTable.get() + newCapacity, -1);
    // Rehash using the NEW capacity and resolve every collision again.
    for (int i = 0; i < capacity; ++i) {
        if (table[i] == -1) continue;
        int index = table[i] % newCapacity;
        while (newTable[index] != -1) index = (index + 1) % newCapacity;
        newTable[index] = table[i];
    }
    delete[] table;
    table = newTable.release();
    capacity = newCapacity;
}

Hashtable::Hashtable(const std::string& filename)
    : table(nullptr), capacity(10), numElements(0) {
    std::ifstream input(filename.c_str());
    if (!input) throw std::runtime_error("Cannot open " + filename);
    table = new int[capacity];
    std::fill(table, table + capacity, -1);
    try {
        int value;
        while (input >> value) insert(value);
        if (!input.eof()) throw std::runtime_error("Invalid integer in " + filename);
    } catch (...) {
        delete[] table;
        throw;
    }
}
Hashtable::~Hashtable() { delete[] table; }
int Hashtable::getSize() const { return numElements; }

std::string Hashtable::search(int number) const {
    if (number < 0) return "FAILURE";
    int index = hashFunction(number);
    // Bound probing even if a future change allows a completely full table.
    for (int visited = 0; visited < capacity; ++visited) {
        if (table[index] == -1) return "FAILURE";
        if (table[index] == number) return "SUCCESS";
        index = (index + 1) % capacity;
    }
    return "FAILURE";
}
void Hashtable::insert(int number) {
    if (number < 0) throw std::invalid_argument("Values must be nonnegative");
    // Keep an empty slot available and avoid very long probing chains.
    if (numElements >= capacity / 2) resize();
    int index = hashFunction(number);
    while (table[index] != -1) index = (index + 1) % capacity;
    table[index] = number;
    ++numElements;
}
