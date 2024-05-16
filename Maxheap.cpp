#include "Maxheap.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

void Maxheap::heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void Maxheap::heapifyDown(int index) {
    int size = heap.size();
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

Maxheap::Maxheap(std::string& filename) {
    std::ifstream file(filename);
    int number;
    while (file >> number) {
        insert(number);
    }
    file.close();
}

int Maxheap::getSize() {
    return heap.size();
}

int Maxheap::findMax() {
    if (heap.empty()) 
        throw std::runtime_error("Η σωρός είναι άδεια");
    return heap[0];
}

void Maxheap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void Maxheap::deleteMax() {
    if (heap.empty()) 
        throw std::runtime_error("Η σωρός είναι άδεια");
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) 
        heapifyDown(0);
}