#include "Minheap.h"
#include "Maxheap.h"
#include "Avltree.h"
#include "Hashtable.h"
#include "Graph.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
int checks = 0;
void check(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
template<class Function> void expectError(Function function, const char* message) {
    ++checks;
    try { function(); } catch (const std::exception&) { return; }
    throw std::runtime_error(message);
}
}
int main() {
    const std::string empty = "tests/fixtures/empty.txt";
    const std::string numbers = "tests/fixtures/integers.txt";
    const std::string graphFile = "tests/fixtures/graph-connected.txt";
    try {
        Minheap minimum(empty);
        Maxheap maximum(empty);
        for (int number = 99; number >= 0; --number) {
            minimum.insert(number); maximum.insert(number);
        }
        check(minimum.getSize() == 100 && maximum.getSize() == 100, "Heap expansion");
        for (int number = 0; number < 100; ++number) {
            check(minimum.findMin() == number, "Minheap sorted removal");
            check(maximum.findMax() == 99 - number, "Maxheap sorted removal");
            minimum.deleteMin(); maximum.deleteMax();
        }
        expectError([&]() { minimum.findMin(); }, "Empty minheap query");
        expectError([&]() { maximum.deleteMax(); }, "Empty maxheap deletion");
        expectError([&]() { minimum.insert(-1); }, "Negative heap value");
        Minheap fromFile(numbers);
        check(fromFile.getSize() == 5 && fromFile.findMin() == 1, "Heap file initialization");

        Avltree tree(empty);
        expectError([&]() { tree.findMin(); }, "Empty AVL must not dereference null");
        for (int number = 0; number < 100; ++number) tree.insert(number);
        tree.insert(50);
        check(tree.getSize() == 100, "AVL unique keys");
        for (int number = 0; number < 100; ++number) check(tree.search(number) == "SUCCESS", "AVL search after rotations");
        for (int number = 0; number < 100; number += 2) tree.deleteAvl(number);
        check(tree.getSize() == 50 && tree.findMin() == 1, "AVL deletion and minimum");
        for (int number = 0; number < 100; ++number)
            check(tree.search(number) == (number % 2 ? "SUCCESS" : "FAILURE"), "AVL deletion search");
        for (int number = 1; number < 100; number += 2) tree.deleteAvl(number);
        check(tree.getSize() == 0, "AVL completely deleted");
        expectError([&]() { tree.findMin(); }, "AVL minimum after deleting last key");

        Hashtable table(empty);
        for (int number = 1; number <= 1001; number += 10) table.insert(number);
        check(table.getSize() == 101, "Hash table size across repeated rehashing");
        for (int number = 1; number <= 1001; number += 10)
            check(table.search(number) == "SUCCESS", "Hash collision survives resize");
        check(table.search(9999) == "FAILURE", "Missing hash key terminates");
        table.insert(1);
        check(table.getSize() == 102 && table.search(1) == "SUCCESS", "Hash duplicates retained");
        expectError([&]() { table.insert(-1); }, "Negative hash value");

        Graph graph(graphFile);
        check(graph.getSize() == std::make_pair(4, 5), "Undirected graph size");
        check(graph.shortestPath(0, 3) == 7 && graph.shortestPath(3, 0) == 7, "Both edge directions traversable");
        check(graph.shortestPath(2, 2) == 0, "Path to same vertex");
        check(graph.spanningTreeCost() == 7, "Minimum spanning tree cost");
        check(graph.connectedComponents() == 1, "Connected graph");
        graph.insertEdge(1, 0, 99);
        check(graph.getSize().second == 5 && graph.shortestPath(0, 1) == 4, "Reverse duplicate ignored");
        graph.insertEdge(3, 3, 0);
        check(graph.getSize().second == 6 && graph.spanningTreeCost() == 7, "Self loop counted once, excluded from MST");
        graph.deleteEdge(1, 0);
        check(graph.shortestPath(0, 3) == 12 && graph.shortestPath(3, 0) == 12, "Delete removes both edge directions");
        graph.deleteEdge(0, 2);
        check(graph.connectedComponents() == 2, "Isolated vertex remains after edge deletion");
        check(graph.spanningTreeCost() == -1 && graph.shortestPath(0, 3) == -1, "Disconnected graph handled");
        expectError([&]() { graph.shortestPath(0, 999); }, "Unknown vertex");
        expectError([&]() { graph.insertEdge(0, 1, -1); }, "Negative weight rejected");
        Graph noVertices(empty);
        check(noVertices.getSize() == std::make_pair(0, 0), "Empty graph size");
        check(noVertices.connectedComponents() == 0 && noVertices.spanningTreeCost() == 0, "Empty graph algorithms");
        std::cout << checks << " structure checks passed\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n'; return 1;
    }
}
