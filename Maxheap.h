#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>

class Maxheap {

  private:

    std::vector<int> heap;

    void heapifyUp(int index);

    void heapifyDown(int index);

public:

    Maxheap(std::string& filename);

    int getSize();

    int findMax();

    void insert(int value);

    void deleteMax();
};

#endif //MAXHEAP_H