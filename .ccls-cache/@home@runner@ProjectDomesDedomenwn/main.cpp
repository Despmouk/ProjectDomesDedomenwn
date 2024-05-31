#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <chrono>
#include <stdexcept>
#include <utility>
#include "Minheap.h"
#include "Maxheap.h"
#include "Avltree.h"
#include "Graph.h"
#include "Hashtable.h"

using namespace std;

int sameStrings(char A[], char B[]){
  int i = 0;
  while(A[i] != '\0' && B[i] != '\0'){
    if(A[i] != B[i]){
      return 0;
    }
    i++;
  }
  return 1;
}

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
        if (sameStrings(s, s1)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Minheap minh(filename1);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο σωρός ελαχίστων κατασκευάστηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s2)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Maxheap maxh(filename2);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο σωρός μεγίστων κατασκευάστηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s3)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Avltree avlt(filename3);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το δυαδικό δένδρο αναζήτησης κατασκευάστηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s4)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Graph gra(filename4);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το γράφημα κατασκευάστηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s5)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          Hashtable hash(filename5);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο πίνακας κατακερματισμού κατασκευάστηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s6)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του σωρού ελαχίστων είναι " << minh.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s7)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του σωρού μεγίστων είναι " << maxh.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s8)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του δυαδικού δένδρου αναζήτησης είναι " << avlt.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s9)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          auto size = gra.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το πλήθος των κορυφών του γράφου είναι " << size.first << " και το πλήθος των ακμών είναι " << size.second; 
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s10)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το πλήθος των στοιχείων του πίνακα κατακερματισμού είναι " << hash.getSize();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s11)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το ελάχιστο στοιχείο από το σωρό ελαχίστων είναι " << minh.findMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s12)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το μέγιστο στοιχείο από το σωρό μεγίστων είναι " << maxh.findMax();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s13)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          outf << "Το ελάχιστο στοιχείο από το δυαδικό δένδρο αναζήτησης είναι " << avlt.findMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << ", το οποίο ανακτήθηκε σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s14)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.search(12);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          if (avlt.search(12)=="SUCCESS")
            outf << "Ο αριθμός αναζητήθηκε στο δυαδικό δένδρο σε " << diff.count() << " δευτερόλεπτα και βρέθηκε." << endl;
          else
            outf << "Ο αριθμός αναζητήθηκε στο δυαδικό δένδρο σε " << diff.count() << " δευτερόλεπτα αλλά δεν βρέθηκε." << endl;
        }
        else if (sameStrings(s, s15)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          hash.search(12);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          if (hash.search(12)=="SUCCESS")
            outf << "Ο αριθμός αναζητήθηκε στον πίνακα κατακερματισμού σε " << diff.count() << " δευτερόλεπτα και βρέθηκε." << endl;
          else
            outf << "Ο αριθμός αναζητήθηκε στον πίνακα κατακερματισμού σε " << diff.count() << " δευτερόλεπτα αλλά δεν βρέθηκε." << endl;
        }
        else if (sameStrings(s, s16)==1)
        {
          
        }
        else if (sameStrings(s, s17)==1)
        {
          
        }
        else if (sameStrings(s, s18)==1)
        {
          
        }
        else if (sameStrings(s, s19)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε στον σωρό ελαχίστων σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s20)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          maxh.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε στον σωρό μεγίστων σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s21)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε στο δυαδικό δένδρο αναζήτησης σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s22)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          hash.insert(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Ο αριθμός εισάχθηκε στον πίνακα κατακερματισμού σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s23)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          gra.addEdge(2,4,10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Η ακμή εισάχθηκε στο γράφημα σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s24)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          minh.deleteMin();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το ελάχιστο στοιχείο διαγράφτηκε από τον σωρό ελαχίστων σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s25)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          maxh.deleteMax();
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το μέγιστο στοιχείο διαγράφτηκε από τον σωρό μεγίστων σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s26)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          avlt.deleteAvl(10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Το στοιχείο διαγράφτηκε από το δυαδικό δένδρο αναζήτησης σε " << diff.count() << " δευτερόλεπτα." << endl;
        }
        else if (sameStrings(s, s27)==1)
        {
          auto start = std::chrono::high_resolution_clock::now();
          gra.removeEdge(2,4,10);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> diff = end - start;
          outf << "Η ακμή διαγράφτηκε απο το γράφημα σε " << diff.count() << " δευτερόλεπτα." << endl;
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
