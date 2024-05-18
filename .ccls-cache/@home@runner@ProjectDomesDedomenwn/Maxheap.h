#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>

class Maxheap {

  private:

    int* heap;       // Δυναμικός πίνακας για την αποθήκευση των στοιχείων
    
    int capacity;    // Χωρητικότητα του σωρού
    
    int size;        // Τρέχων αριθμός στοιχείων στο σωρο

    void expandHeap();

    void heapifyUp(int index);

    void heapifyDown(int index);

  public:

    Maxheap(std::string& filename);

    ~Maxheap();

    int getSize();

    int findMax();

    void insert(int value);

    void deleteMax();
};

#endif //MAXHEAP_H