#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int Hashtable::hashFunction(int number) {
    return number % capacity;  
}

void Hashtable::resize() {
    int newCapacity = capacity * 2;
    int* newTable = new int[newCapacity];
    std::fill(newTable, newTable + newCapacity, -1);

    for (int i = 0; i < capacity; i++) {
        if (table[i] != -1) {
            int newIndex = hashFunction(table[i]);
            newTable[newIndex] = table[i]; 
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

Hashtable::Hashtable(std::string& filename) : capacity(10), numElements(0) {
    table = new int[capacity];
    std::fill(table, table + capacity, -1);

    std::ifstream file(filename);
    int number;
    while (file >> number) {
        if (numElements == capacity) {
            resize();  
        }
        int index = hashFunction(number);
        while (table[index] != -1) {  
            index = (index + 1) % capacity;
        }
        table[index] = number;
        numElements++;
    }
    file.close();
}

Hashtable::~Hashtable() {
    delete[] table;
}

int Hashtable::getSize() {
    return numElements;
}

std::string Hashtable::search(int number) {
    int index = hashFunction(number);
    while (table[index] != -1 && table[index] != number) {
        index = (index + 1) % capacity;
    }
    return (table[index] == number) ? "SUCCESS" : "FAILURE";
}

void Hashtable::insert(int number) {
    if (numElements >= capacity) {
        resize();  
    }

    int index = hashFunction(number);
    while (table[index] != -1) {  
        index = (index + 1) % capacity;
    }
    table[index] = number;
    numElements++;
}