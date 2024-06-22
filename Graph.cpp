#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

using namespace std;

Graph::Vertex* Graph::findVertex(int id) {
    Vertex* temp = vertices;
    while (temp != nullptr) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void Graph::addVertex(int id) {
    if (findVertex(id) == nullptr) {
        Vertex* newVertex = new Vertex{id, nullptr, vertices};
        vertices = newVertex;
        numVertices++;
    }
}

Graph::Edge* Graph::findEdge(int node1, int node2) {
    Vertex* vertex = findVertex(node1);
    if (vertex != nullptr) {
        Edge* edge = vertex->edgeList;
        while (edge != nullptr) {
            if (edge->node2 == node2)
                return edge;
            edge = edge->next;
        }
    }
    return nullptr;
}

Graph::Graph(std::string& filename) : vertices(nullptr), numVertices(0), numEdges(0) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int node1, node2, weight;
        iss >> node1 >> node2 >> weight;
        insertEdge(node1, node2, weight);
    }
    file.close();
}

Graph::~Graph() {
    while (vertices != nullptr) {
        Vertex* tempVertex = vertices;
        vertices = vertices->next;

        Edge* edge = tempVertex->edgeList;
        while (edge != nullptr) {
            Edge* tempEdge = edge;
            edge = edge->next;
            delete tempEdge;
        }
        delete tempVertex;
    }
}

std::pair<int, int> Graph::getSize() {
    return std::make_pair(numVertices, numEdges);
}

void Graph::insertEdge(int node1, int node2, int weight) {
    if (!findEdge(node1, node2)) {
        addVertex(node1);
        addVertex(node2);

        Edge* newEdge = new Edge{node1, node2, weight, findVertex(node1)->edgeList};
        findVertex(node1)->edgeList = newEdge;
        numEdges++;
    }
}

void Graph::deleteEdge(int node1, int node2, int weight) {
    Vertex* vertex = findVertex(node1);
    if (vertex != nullptr) {
        Edge** edge = &vertex->edgeList;
        while (*edge != nullptr) {
            if ((*edge)->node2 == node2 && (*edge)->weight == weight) {
                Edge* temp = *edge;
                *edge = (*edge)->next;
                delete temp;
                numEdges--;
                return;
            }
            edge = &(*edge)->next;
        }
    }
}