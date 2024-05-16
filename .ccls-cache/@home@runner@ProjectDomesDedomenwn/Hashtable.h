#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>

class Hashtable {

  private:

    int* table;       // Δυναμικός πίνακας για την αποθήκευση των στοιχείων
    
    int capacity;     // Τρέχον μέγεθος του πίνακα
    
    int numElements;  // Αριθμός των στοιχείων του πίνακα

    int hashFunction(int number);

    void resize();

  public:

    Hashtable(std::string& filename);

    ~Hashtable();

    int getSize();

    std::string search(int number);

    void insert(int number);

};

#endif //HASHTABLE_H