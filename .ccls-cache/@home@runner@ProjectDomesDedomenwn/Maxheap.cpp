#include "Maxheap.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void Maxheap::expandHeap() {
    int newCapacity = capacity * 2;
    int* newHeap = new int[newCapacity];
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

void Maxheap::heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void Maxheap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

Maxheap::Maxheap(std::string& filename) : capacity(10), size(0) {
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

Maxheap::~Maxheap() {
    delete[] heap;
}

int Maxheap::getSize() {
    return size;
}

int Maxheap::findMax() {
    if (size == 0) 
        throw std::runtime_error("Ο σωρός είναι άδειος");
    return heap[0];
}

void Maxheap::insert(int value) {
    if (size == capacity) {
        expandHeap();
    }
    heap[size] = value;
    heapifyUp(size);
    size++;
}

void Maxheap::deleteMax() {
    if (size == 0) 
        throw std::runtime_error("Ο σωρός είναι άδειος");
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
}