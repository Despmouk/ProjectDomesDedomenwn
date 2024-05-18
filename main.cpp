#include <iostream>
#include <fstream>
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
  std::string filename1 = "inputMinheap.txt";
  Minheap minh(filename1);
  std::string filename2 = "inputMaxheap.txt";
  Maxheap maxh(filename2);
  std::string filename3 = "inputAvltree.txt";
  Avltree avlt(filename3);
  std::string filename4 = "inputGraph.txt";
  Graph gra(filename4);
  std::string filename5 = "inputHashtable.txt";
  Hashtable hash(filename5);
  ifstream inf; // Δηλώνω ένα ρεύμα εισόδου inf
  ofstream outf; // Δηλώνω ένα ρεύμα εξόδου outf
  char s[50];
  char s1[50]="BUILD MINHEAP filename";
  char s2[50]="BUILD MAXHEAP filename";
  char s3[50]="BUILD AVLTREE filename";
  char s4[50]="BUILD GRAPH filename";
  char s5[50]="BUILD HASHTABLE filename";
  char s6[50]="GETSIZE MINHEAP";
  char s7[50]="GETSIZE MAXHEAP";
  char s8[50]="GETSIZE AVLTREE";
  char s9[50]="GETSIZE GRAPH";
  char s10[50]="GETSIZE HASHTABLE";
  char s11[50]="FINDMIN MINHEAP";
  char s12[50]="FINDMAX MAXHEAP";
  char s13[50]="FINDMIN AVLTREE";
  char s14[50]="SEARCH AVLTREE number" ;
  char s15[50]="SEARCH HASHTABLE number";
  char s16[50]="COMPUTESHORTESTPATH GRAPH number1 number2";
  char s17[50]="COMPUTESPANNINGTREE GRAPH";
  char s18[50]="FINDCONNECTEDCOMPONENTS GRAPH";
  char s19[50]="INSERT MINHEAP number";
  char s20[50]="INSERT MAXHEAP number";
  char s21[50]="INSERT AVLTREE number";
  char s22[50]="INSERT HASHTABLE number";
  char s23[50]="INSERT GRAPH number1 number 2";
  char s24[50]="DELETEMIN MINHEAP";
  char s25[50]="DELETEMAX MAXHEAP";
  char s26[50]="DELETE AVLTREE number";
  char s27[50]="DELETE GRAPH number1 number2";
  inf.open("commands.txt"); // Άνοιγμα αρχείου "commands.txt" για ανάγνωση
  outf.open("output.txt"); // Άνοιγμα αρχείου "output.txt" για εγγραφή
  if (inf.is_open() && outf.is_open())
  {
    while (inf.getline(s, 50))
      {
        if (strcmp(s, s1)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Minheap minh(filename1);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο σωρός ελαχίστων χτίστηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s2)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Maxheap maxh(filename2);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο σωρός μεγίστων χτίστηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s3)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Avltree avlt(filename3);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το δυαδικό δένδρο αναζήτησης χτίστηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s4)==0)
        {
          
        }
        else if (strcmp(s, s5)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Hashtable hash(filename5);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο πίνακας κατακερματισμού χτίστηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s6)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του σωρού ελαχίστων είναι " << minh.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s7)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του σωρού μεγίστων είναι " << maxh.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s8)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του δένδρου είναι " << avlt.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s9)==0)
        {
          
        }
        else if (strcmp(s, s10)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του πίνακα είναι " << hash.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s11)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το ελάχιστο στοιχείο από το σωρό ελαχίστων είναι " << minh.findMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s12)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το μέγιστο στοιχείο από το σωρό μεγίστων είναι " << maxh.findMax();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s13)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το ελάχιστο στοιχείο από το δένδρο είναι " << avlt.findMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << " το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s14)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.search(12);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός αναζητήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s15)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          hash.search(12);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός αναζητήθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s16)==0)
        {
          
        }
        else if (strcmp(s, s17)==0)
        {
          
        }
        else if (strcmp(s, s18)==0)
        {
          
        }
        else if (strcmp(s, s19)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s20)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          maxh.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s21)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s22)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          hash.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s23)==0)
        {
          
        }
        else if (strcmp(s, s24)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.deleteMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο ελάχιστος διαγράφτηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s25)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          maxh.deleteMax();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο μέγιστος διαγράφτηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s26)==0)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.deleteAvl(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το στοιχείο διαγράφτηκε σε " << diff.count() << " δευτερόλεπτα" << endl;
        }
        else if (strcmp(s, s27)==0)
        {
          
        }
      }
    inf.close();
    outf.close();
  } 
  else
  {
   cerr << "Δεν μπόρεσε να ανοίξει το αρχείο" << endl;   
  }
}
