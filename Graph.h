#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <utility>

// Undirected weighted graph. Each non-loop edge has two adjacency entries.
class Graph {
    struct Edge { int node2; int weight; Edge* next; };
    struct Vertex { int id; Edge* edgeList; Vertex* next; };
    Vertex* vertices;
    int numVertices;
    int numEdges;
    Vertex* findVertex(int id) const;
    void addVertex(int id);
    Edge* findEdge(int node1, int node2) const;
    void clear();
    bool removeAdjacency(int node1, int node2);
public:
    explicit Graph(const std::string& filename);
    ~Graph();
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;
    std::pair<int, int> getSize() const;
    void insertEdge(int node1, int node2, int weight);
    void deleteEdge(int node1, int node2);
    // -1 means no path / no spanning tree. Valid costs are nonnegative.
    long long shortestPath(int node1, int node2) const;
    long long spanningTreeCost() const;
    int connectedComponents() const;
};
#endif
