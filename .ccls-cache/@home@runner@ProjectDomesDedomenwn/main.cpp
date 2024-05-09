#include <iostream>
#include <fstream>
#include <cstring>
#include "Minheap.h"
#include "Maxheap.h"
#include "Avltree.h"
#include "Graph.h"
#include "Hashtable.h"

using namespace std;

int main() { 
  //Δημιουργία αντικειμένων.
  Minheap minh;
  Maxheap maxh;
  Avltree avlt;
  Graph gra;
  Hashtable hash;
  ifstream inf;
  char s[50];
  //Ανοιγμα αρχείου για ανάγνωση.
  string filename;
  filename = "commands.txt";
  inf.open(filename);
  if (inf.is_open())
  {
    while (inf.getline(s, 50))
      cout<< s << endl;
      {
        if (strcmp(s, "BUILD MINHEAP input_minheap.txt")==0)
        {
          
        }
        else if (strcmp(s, "BUILD MAXHEAP input_maxheap.txt")==0)
        {
          
        }
        else if (strcmp(s, "BUILD AVLTREE input_avltree.txt")==0)
        {
          
        }
        else if (strcmp(s, "BUILD GRAPH input_graph.txt")==0)
        {
          
        }
        else if (strcmp(s, "BUILD HASHTABLE input_hashtable.txt")==0)
        {
          
        }
        else if (strcmp(s, "GETSIZE MINHEAP")==0)
        {
          
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
  } 
  else
  {
   cerr << "Could not open file" << endl;   
  }
  ofstream outf;
}
