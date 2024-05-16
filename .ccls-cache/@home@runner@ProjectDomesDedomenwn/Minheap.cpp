#include "Minheap.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

void Minheap::heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void Minheap::heapifyDown(int index) {
    int size = heap.size();
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

Minheap::Minheap(std::string& filename) {
    std::ifstream file(filename);
    int number;
    while (file >> number) {
        insert(number);
    }
    file.close();
}

int Minheap::getSize() {
    return heap.size();
}

int Minheap::findMin() {
    if (heap.empty())
        throw std::runtime_error("Η σωρός είναι άδεια");
    return heap[0];
}

void Minheap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void Minheap::deleteMin() {
    if (heap.empty())
        throw std::runtime_error("Η σωρός είναι άδεια");
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) 
        heapifyDown(0);
}