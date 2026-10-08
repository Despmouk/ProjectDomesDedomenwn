#include "Avltree.h"
#include "Graph.h"
#include "Hashtable.h"
#include "Maxheap.h"
#include "Minheap.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
struct Structures {
    std::unique_ptr<Minheap> minheap;
    std::unique_ptr<Maxheap> maxheap;
    std::unique_ptr<Avltree> avltree;
    std::unique_ptr<Graph> graph;
    std::unique_ptr<Hashtable> hashtable;
};
template<class T> T& requireBuilt(std::unique_ptr<T>& object) {
    if (!object) throw std::logic_error("Use BUILD before accessing this structure");
    return *object;
}
int readNumber(std::istringstream& input) {
    int number;
    if (!(input >> number) || number < 0)
        throw std::invalid_argument("Expected a nonnegative integer");
    return number;
}
void requireEnd(std::istringstream& input) {
    std::string extra;
    if (input >> extra) throw std::invalid_argument("Unexpected extra argument");
}
std::string execute(const std::string& line, Structures& state) {
    std::istringstream input(line);
    std::string action, type;
    if (!(input >> action >> type)) throw std::invalid_argument("Expected command and structure");
    if (action == "BUILD") {
        std::string filename;
        if (!(input >> filename)) throw std::invalid_argument("Expected filename");
        requireEnd(input);
        // Successful BUILD replaces the old instance and releases its memory.
        if (type == "MINHEAP") state.minheap.reset(new Minheap(filename));
        else if (type == "MAXHEAP") state.maxheap.reset(new Maxheap(filename));
        else if (type == "AVLTREE") state.avltree.reset(new Avltree(filename));
        else if (type == "GRAPH") state.graph.reset(new Graph(filename));
        else if (type == "HASHTABLE") state.hashtable.reset(new Hashtable(filename));
        else throw std::invalid_argument("Unknown structure");
        return "BUILT";
    }
    if (action == "GETSIZE") {
        requireEnd(input);
        if (type == "MINHEAP") return std::to_string(requireBuilt(state.minheap).getSize());
        if (type == "MAXHEAP") return std::to_string(requireBuilt(state.maxheap).getSize());
        if (type == "AVLTREE") return std::to_string(requireBuilt(state.avltree).getSize());
        if (type == "HASHTABLE") return std::to_string(requireBuilt(state.hashtable).getSize());
        if (type == "GRAPH") {
            std::pair<int, int> size = requireBuilt(state.graph).getSize();
            return std::to_string(size.first) + " " + std::to_string(size.second);
        }
    } else if (action == "FINDMIN" || action == "FINDMAX") {
        requireEnd(input);
        if (action == "FINDMIN" && type == "MINHEAP") return std::to_string(requireBuilt(state.minheap).findMin());
        if (action == "FINDMIN" && type == "AVLTREE") return std::to_string(requireBuilt(state.avltree).findMin());
        if (action == "FINDMAX" && type == "MAXHEAP") return std::to_string(requireBuilt(state.maxheap).findMax());
    } else if (action == "SEARCH") {
        int number = readNumber(input); requireEnd(input);
        if (type == "AVLTREE") return requireBuilt(state.avltree).search(number);
        if (type == "HASHTABLE") return requireBuilt(state.hashtable).search(number);
    } else if (action == "INSERT") {
        int first = readNumber(input);
        if (type == "GRAPH") {
            int second = readNumber(input), weight = readNumber(input); requireEnd(input);
            requireBuilt(state.graph).insertEdge(first, second, weight);
        } else {
            requireEnd(input);
            if (type == "MINHEAP") requireBuilt(state.minheap).insert(first);
            else if (type == "MAXHEAP") requireBuilt(state.maxheap).insert(first);
            else if (type == "AVLTREE") requireBuilt(state.avltree).insert(first);
            else if (type == "HASHTABLE") requireBuilt(state.hashtable).insert(first);
            else throw std::invalid_argument("Unknown structure");
        }
        return "OK";
    } else if (action == "DELETE") {
        int first = readNumber(input);
        if (type == "GRAPH") {
            int second = readNumber(input); requireEnd(input);
            requireBuilt(state.graph).deleteEdge(first, second);
        } else if (type == "AVLTREE") {
            requireEnd(input); requireBuilt(state.avltree).deleteAvl(first);
        } else throw std::invalid_argument("DELETE is supported only for AVLTREE and GRAPH");
        return "OK";
    } else if (action == "DELETEMIN" && type == "MINHEAP") {
        requireEnd(input); requireBuilt(state.minheap).deleteMin(); return "OK";
    } else if (action == "DELETEMAX" && type == "MAXHEAP") {
        requireEnd(input); requireBuilt(state.maxheap).deleteMax(); return "OK";
    } else if (action == "COMPUTESHORTESTPATH" && type == "GRAPH") {
        int first = readNumber(input), second = readNumber(input); requireEnd(input);
        long long cost = requireBuilt(state.graph).shortestPath(first, second);
        return cost < 0 ? "UNREACHABLE" : std::to_string(cost);
    } else if (action == "COMPUTESPANNINGTREE" && type == "GRAPH") {
        requireEnd(input);
        long long cost = requireBuilt(state.graph).spanningTreeCost();
        return cost < 0 ? "NO_SPANNING_TREE" : std::to_string(cost);
    } else if (action == "FINDCONNECTEDCOMPONENTS" && type == "GRAPH") {
        requireEnd(input); return std::to_string(requireBuilt(state.graph).connectedComponents());
    }
    throw std::invalid_argument("Unsupported command");
}
}
int main() {
    // File I/O only: no keyboard input, stdout, or stderr.
    std::ofstream output("output.txt");
    if (!output) return 1;
    std::ifstream commands("commands.txt");
    if (!commands) { output << "ERROR: Cannot open commands.txt\n"; return 1; }
    Structures state;
    std::string line;
    while (std::getline(commands, line)) {
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        const auto start = std::chrono::steady_clock::now();
        std::string result;
        try { result = execute(line, state); }
        catch (const std::exception& error) { result = std::string("ERROR: ") + error.what(); }
        const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
        output << line << " | " << result << " | " << std::fixed << std::setprecision(9)
               << elapsed.count() << " s\n";
        if (!output) return 1;
    }
    return commands.bad() ? 1 : 0;
}
