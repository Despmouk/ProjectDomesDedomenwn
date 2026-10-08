#include "Graph.h"
#include <fstream>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

Graph::Vertex* Graph::findVertex(int id) const {
    for (Vertex* v = vertices; v; v = v->next) if (v->id == id) return v;
    return nullptr;
}
void Graph::addVertex(int id) {
    if (!findVertex(id)) {
        vertices = new Vertex{id, nullptr, vertices};
        ++numVertices;
    }
}
Graph::Edge* Graph::findEdge(int node1, int node2) const {
    Vertex* v = findVertex(node1);
    if (v) for (Edge* e = v->edgeList; e; e = e->next)
        if (e->node2 == node2) return e;
    return nullptr;
}
Graph::Graph(const std::string& filename)
    : vertices(nullptr), numVertices(0), numEdges(0) {
    std::ifstream input(filename.c_str());
    if (!input) throw std::runtime_error("Cannot open " + filename);
    try {
        std::string line;
        while (std::getline(input, line)) {
            if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
            std::istringstream record(line);
            int node1, node2, weight;
            std::string extra;
            if (!(record >> node1 >> node2 >> weight) || (record >> extra))
                throw std::runtime_error("Expected node1 node2 weight in " + filename);
            insertEdge(node1, node2, weight);
        }
        if (input.bad()) throw std::runtime_error("Cannot read " + filename);
    } catch (...) { clear(); throw; }
}
void Graph::clear() {
    while (vertices) {
        Vertex* vertex = vertices;
        vertices = vertices->next;
        while (vertex->edgeList) {
            Edge* edge = vertex->edgeList;
            vertex->edgeList = edge->next;
            delete edge;
        }
        delete vertex;
    }
    numVertices = numEdges = 0;
}
Graph::~Graph() { clear(); }
std::pair<int, int> Graph::getSize() const {
    return std::make_pair(numVertices, numEdges);
}
void Graph::insertEdge(int node1, int node2, int weight) {
    if (node1 < 0 || node2 < 0 || weight < 0)
        throw std::invalid_argument("Vertex IDs and edge weights must be nonnegative");
    if (findEdge(node1, node2)) return;
    // Allocate both adjacency entries before linking either one.
    std::unique_ptr<Edge> forward(new Edge{node2, weight, nullptr});
    std::unique_ptr<Edge> backward;
    if (node1 != node2) backward.reset(new Edge{node1, weight, nullptr});
    addVertex(node1);
    addVertex(node2);
    Vertex* first = findVertex(node1);
    forward->next = first->edgeList;
    first->edgeList = forward.release();
    if (node1 != node2) {
        Vertex* second = findVertex(node2);
        backward->next = second->edgeList;
        second->edgeList = backward.release();
    }
    ++numEdges; // Count the undirected edge only once.
}
bool Graph::removeAdjacency(int node1, int node2) {
    Vertex* v = findVertex(node1);
    if (!v) return false;
    Edge** link = &v->edgeList;
    while (*link) {
        if ((*link)->node2 == node2) {
            Edge* removed = *link;
            *link = removed->next;
            delete removed;
            return true;
        }
        link = &(*link)->next;
    }
    return false;
}
void Graph::deleteEdge(int node1, int node2) {
    if (!removeAdjacency(node1, node2)) return;
    if (node1 != node2) removeAdjacency(node2, node1);
    --numEdges;
    // Vertices remain, including newly isolated vertices.
}
long long Graph::shortestPath(int node1, int node2) const {
    if (!findVertex(node1) || !findVertex(node2))
        throw std::invalid_argument("Vertex does not exist");
    const long long infinity = std::numeric_limits<long long>::max();
    std::map<int, long long> distance;
    std::map<int, Vertex*> byId;
    for (Vertex* v = vertices; v; v = v->next) {
        distance[v->id] = infinity;
        byId[v->id] = v;
    }
    typedef std::pair<long long, int> State;
    std::priority_queue<State, std::vector<State>, std::greater<State> > pending;
    distance[node1] = 0;
    pending.push(State(0, node1));
    // Dijkstra: obsolete queue entries are skipped after a shorter path is found.
    while (!pending.empty()) {
        State state = pending.top(); pending.pop();
        if (state.first != distance[state.second]) continue;
        if (state.second == node2) return state.first;
        for (Edge* e = byId[state.second]->edgeList; e; e = e->next) {
            if (state.first > infinity - e->weight) continue;
            long long candidate = state.first + e->weight;
            if (candidate < distance[e->node2]) {
                distance[e->node2] = candidate;
                pending.push(State(candidate, e->node2));
            }
        }
    }
    return -1;
}
long long Graph::spanningTreeCost() const {
    if (!vertices) return 0;
    std::map<int, Vertex*> byId;
    for (Vertex* v = vertices; v; v = v->next) byId[v->id] = v;
    typedef std::pair<long long, int> State;
    std::priority_queue<State, std::vector<State>, std::greater<State> > pending;
    std::set<int> visited;
    pending.push(State(0, vertices->id));
    long long total = 0;
    // Prim: accept the cheapest edge reaching a vertex outside the current tree.
    while (!pending.empty()) {
        State state = pending.top(); pending.pop();
        if (!visited.insert(state.second).second) continue;
        if (total > std::numeric_limits<long long>::max() - state.first)
            throw std::overflow_error("Spanning tree cost is too large");
        total += state.first;
        for (Edge* e = byId[state.second]->edgeList; e; e = e->next)
            if (!visited.count(e->node2)) pending.push(State(e->weight, e->node2));
    }
    return visited.size() == static_cast<std::size_t>(numVertices) ? total : -1;
}
int Graph::connectedComponents() const {
    std::map<int, Vertex*> byId;
    for (Vertex* v = vertices; v; v = v->next) byId[v->id] = v;
    std::set<int> visited;
    int count = 0;
    for (Vertex* v = vertices; v; v = v->next) {
        if (!visited.insert(v->id).second) continue;
        ++count;
        std::queue<int> pending;
        pending.push(v->id);
        while (!pending.empty()) {
            int id = pending.front(); pending.pop();
            for (Edge* e = byId[id]->edgeList; e; e = e->next)
                if (visited.insert(e->node2).second) pending.push(e->node2);
        }
    }
    return count;
}
