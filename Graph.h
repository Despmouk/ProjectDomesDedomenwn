#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

class Graph {

  private:

    struct Edge {
        int node1;
        int node2;
        int weight;
        Edge* next;
    };

    struct Vertex {
        int id;
        Edge* edgeList;
        Vertex* next;
    };

    Vertex* vertices;
    int numVertices;
    int numEdges;

    Vertex* findVertex(int id);

    void addVertex(int id);

    Edge* findEdge(int node1, int node2);

  public:

    Graph(std::string& filename);

    ~Graph();

    std::pair<int, int> getSize();

    void insertEdge(int node1, int node2, int weight);

    void deleteEdge(int node1, int node2, int weight);

};

#endif //GRAPH_H