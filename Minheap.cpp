#include "Minheap.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void Minheap::expandHeap() {
    int newCapacity = capacity * 2;
    int* newHeap = new int[newCapacity];
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

void Minheap::heapifyUp(int index) {
    while (index != 0 && heap[(index - 1) / 2] > heap[index]) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void Minheap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

Minheap::Minheap(std::string& filename) : capacity(10), size(0) {
    heap = new int[capacity];
    std::ifstream file(filename);
    if (!file) 
        throw std::runtime_error("Αποτυχία ανοίγματος αρχείου");
    int number;
    while (file >> number) {
        insert(number);
    }
    file.close();
}

Minheap::~Minheap() {
    delete[] heap;
}

int Minheap::getSize() {
    return size;
}

int Minheap::findMin() {
    if (size <= 0)
        throw std::runtime_error("Ο σωρός είναι άδειος");
    return heap[0];
}

void Minheap::insert(int value) {
    if (size == capacity) {
        expandHeap();
    }
    heap[size] = value;
    heapifyUp(size);
    size++;
}

void Minheap::deleteMin() {
    if (size <= 0)
        throw std::runtime_error("Ο σωρός είναι άδειος");
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
}

