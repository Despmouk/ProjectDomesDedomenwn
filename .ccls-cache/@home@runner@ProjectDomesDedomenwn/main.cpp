#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <chrono>
#include <stdexcept>
#include "Minheap.h"
#include "Maxheap.h"
#include "Avltree.h"
#include "Graph.h"
#include "Hashtable.h"

using namespace std;

int main() { 
  Maxheap maxh("inputMaxheap.txt");
  Avltree avlt("inputAvltree.txt");
  Graph gra("inputGraph.txt");
  Hashtable hash("inputHashtable.txt");
  ifstream inf; // Δηλώνω ένα ρεύμα εισόδου inf
  ofstream outf; // Δηλώνω ένα ρεύμα εξόδου outf
  char s[50];
  inf.open("commands.txt"); // Άνοιγμα αρχείου "commands.txt" για ανάγνωση
  outf.open("output.txt"); // Άνοιγμα αρχείου "output.txt" για εγγραφή
  if (inf.is_open() && outf.is_open())
  {
    while (inf.getline(s, 50))
      {
        if (strcmp(s, "BUILD MINHEAP filename")==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Minheap minh("inputMinheap.txt");
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο σωρός ελαχίστων χτίστηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, "BUILD MAXHEAP filename")==0)
        {
          
        }
        else if (strcmp(s, "BUILD AVLTREE filename")==0)
        {
          
        }
        else if (strcmp(s, "BUILD GRAPH filename")==0)
        {
          
        }
        else if (strcmp(s, "BUILD HASHTABLE filename")==0)
        {
          
        }
        else if (strcmp(s, "GETSIZE MINHEAP")==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του σωρού ελαχίστων είναι " << minh.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, "GETSIZE MAXHEAP")==0)
        {
          
        }
        else if (strcmp(s, "GETSIZE AVLTREE")==0)
        {
          
        }
        else if (strcmp(s, "GETSIZE GRAPH")==0)
        {
          
        }
        else if (strcmp(s, "GETSIZE HASHTABLE")==0)
        {
          
        }
        else if (strcmp(s, "FINDMIN MINHEAP")==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το ελάχιστο στοιχείο από το σωρό ελαχίστων είναι " << minh.findMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, "FINDMAX MAXHEAP")==0)
        {
          
        }
        else if (strcmp(s, "FINDMIN AVLTREE")==0)
        {
          
        }
        else if (strcmp(s, "SEARCH AVLTREE number")==0)
        {
          
        }
        else if (strcmp(s, "SEARCH HASHTABLE number")==0)
        {
          
        }
        else if (strcmp(s, "COMPUTESHORTESTPATH GRAPH number1 number2")==0)
        {
          
        }
        else if (strcmp(s, "COMPUTESPANNINGTREE GRAPH")==0)
        {
          
        }
        else if (strcmp(s, "FINDCONNECTEDCOMPONENTS GRAPH")==0)
        {
          
        }
        else if (strcmp(s, "INSERT MINHEAP number")==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, "INSERT MAXHEAP number")==0)
        {
          
        }
        else if (strcmp(s, "INSERT AVLTREE number")==0)
        {
          
        }
        else if (strcmp(s, "INSERT HASHTABLE number")==0)
        {
          
        }
        else if (strcmp(s, "INSERT GRAPH number1 number 2")==0)
        {
          
        }
        else if (strcmp(s, "DELETEMIN MINHEAP")==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.deleteMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο ελάχιστος διαγράφτηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, "DELETEMAX MAXHEAP ")==0)
        {
          
        }
        else if (strcmp(s, "DELETE AVLTREE number")==0)
        {
          
        }
        else if (strcmp(s, "DELETE GRAPH number1 number2")==0)
        {
          
        }
      }
    inf.close();
    outf.close();
  } 
  else
  {
   cerr << "Could not open file" << endl;   
  }
}
