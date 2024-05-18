#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>

class Minheap {

  private:

    int* heap;        // Δυναμικός πίνακας για την αποθήκευση των στοιχείων
    
    int capacity;     // Χωρητικότητα του σωρού
    
    int size;         // Τρέχων αριθμός στοιχείων στο σωρο

    void expandHeap() {
        int newCapacity = capacity * 2;
        int* newHeap = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void heapifyUp(int index) {
        while (index != 0 && heap[(index - 1) / 2] > heap[index]) {
            std::swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

  public:

    Minheap(std::string& filename) : capacity(10), size(0) {
        heap = new int[capacity];
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Αποτυχία ανοίγματος αρχείου");
        }
        int number;
        while (file >> number) {
            insert(number);
        }
        file.close();
    }

    ~Minheap() {
        delete[] heap;
    }

    void insert(int key) {
        if (size == capacity) {
            expandHeap();
        }
        heap[size] = key;
        heapifyUp(size);
        size++;
    }

    void deleteMin() {
        if (size <= 0)
            throw std::runtime_error("Ο σωρός είναι άδειος");
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    int getMin() const {
        if (size <= 0)
            throw std::runtime_error("Ο σωρός είναι άδειος");
        return heap[0];
    }

    int getSize() const {
        return size;
    }
};

#endif //MINHEAP_H