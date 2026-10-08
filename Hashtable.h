#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

// Open-addressed hash table for nonnegative integers. Duplicates are retained.
class Hashtable {
    int* table;
    int capacity;
    int numElements;
    int hashFunction(int number) const;
    void resize();
public:
    explicit Hashtable(const std::string& filename);
    ~Hashtable();
    Hashtable(const Hashtable&) = delete;
    Hashtable& operator=(const Hashtable&) = delete;
    int getSize() const;
    std::string search(int number) const;
    void insert(int number);
};
#endif
