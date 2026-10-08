#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>

class Minheap {

  private:

    int* heap;       // Δυναμικός πίνακας για την αποθήκευση των στοιχείων
    
    int capacity;    // Χωρητικότητα του σωρού
    
    int size;        // Τρέχων αριθμός στοιχείων στο σωρο

    void expandHeap();

    void heapifyUp(int index);

    void heapifyDown(int index);

  public:

    explicit Minheap(const std::string& filename);

    Minheap(const Minheap&) = delete;
    Minheap& operator=(const Minheap&) = delete;

    ~Minheap();

    int getSize();

    int findMin();

    void insert(int value);

    void deleteMin();
};

#endif //MINHEAP_H