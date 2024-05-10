#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>

class Minheap {

  private:

    std::vector<int> heap;

    void heapifyUp(int index);

    void heapifyDown(int index);

  public:

    Minheap(std::string& filename);

    int getSize();

    int findMin();

    void insert(int number);

    void deleteMin();
};

#endif //MINHEAP_H