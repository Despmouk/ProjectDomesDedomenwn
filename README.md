# Data Structures Library

A C++11 library and command-file runner for min-heaps, max-heaps, AVL trees, an undirected weighted graph, and an open-addressed hash table. Originally developed for a university data structures project in 2024; this revised version corrects command parsing and hashing and completes the graph operations.

## Build and run

Requirements: a C++11 compiler such as `g++`. GNU Make is optional; Python 3 is needed only for integration tests.

From the repository root:

```bash
make
./build/data-structures
```

Without Make:

```bash
g++ -std=c++11 -O2 -Wall -Wextra -Wpedantic main.cpp Minheap.cpp Maxheap.cpp Avltree.cpp Graph.cpp Hashtable.cpp -o data-structures
./data-structures
```

The executable reads `commands.txt` in the current working directory and writes `output.txt`. It does not read keyboard input or print to the console. The included sample executes all 27 command variants.

Each output line contains the original command, its result, and elapsed time in seconds:

```text
COMPUTESHORTESTPATH GRAPH 2 5 | 12 | 0.000012345 s
```

The time shown above is illustrative. Measured times vary between runs.

## Command reference

`TYPE` means `MINHEAP`, `MAXHEAP`, `AVLTREE`, `GRAPH`, or `HASHTABLE`, where the operation supports that type. Values and vertex IDs are nonnegative integers. BUILD must precede use of a structure, but the structures may be built in any order.

| Command | Result or effect |
| --- | --- |
| `BUILD TYPE filename` | Load the named file and replace any previous instance |
| `GETSIZE TYPE` | Number of stored elements; graph returns vertices and undirected edges |
| `FINDMIN MINHEAP` / `FINDMIN AVLTREE` | Minimum value |
| `FINDMAX MAXHEAP` | Maximum value |
| `SEARCH AVLTREE number` / `SEARCH HASHTABLE number` | `SUCCESS` or `FAILURE` |
| `INSERT MINHEAP number` / `INSERT MAXHEAP number` | Add a value to a heap |
| `INSERT AVLTREE number` / `INSERT HASHTABLE number` | Add a key/value |
| `INSERT GRAPH node1 node2 weight` | Add an undirected weighted edge if it does not exist |
| `DELETEMIN MINHEAP` / `DELETEMAX MAXHEAP` | Remove the minimum/maximum |
| `DELETE AVLTREE number` | Delete a key if present |
| `DELETE GRAPH node1 node2` | Delete an edge in both directions if present |
| `COMPUTESHORTESTPATH GRAPH node1 node2` | Shortest-path cost, or `UNREACHABLE` |
| `COMPUTESPANNINGTREE GRAPH` | Minimum spanning-tree cost, or `NO_SPANNING_TREE` |
| `FINDCONNECTEDCOMPONENTS GRAPH` | Number of connected components |

Hash-table deletion is intentionally unsupported, as required by the assignment.

The assignment's INSERT GRAPH row lists two vertex arguments but describes an edge with a weight. This implementation uses the explicit three-argument form above so the weight is supplied rather than guessed.

## Data files and graph behavior

Integer data files contain one nonnegative integer per line. Graph files contain `node1 node2 weight` records. Edge weights are nonnegative, allowing Dijkstra's algorithm.

- Edges are undirected: traversing or deleting an edge works from either endpoint.
- A reverse duplicate is not another edge. The first weight is retained.
- Vertices remain after deleting their last edge, so isolated vertices count as components.
- Self-loops count as one edge and do not reduce shortest paths or enter a spanning tree.
- An empty graph has 0 components and spanning-tree cost 0. A disconnected nonempty graph has no spanning tree.
- Invalid commands, missing files, use before BUILD, and minimum/maximum queries on empty structures are recorded as `ERROR:` results in `output.txt`.

The supplied `inputGraph.txt` has three connected components. Its final record reverses an existing edge, so the graph contains 6 vertices and 3 undirected edges.

## Implementation

| Structure | Implementation |
| --- | --- |
| `Minheap` / `Maxheap` | Manually managed dynamic arrays, sift-up/down, capacity expansion |
| `Avltree` | Height-balanced nodes, rotations, search, insertion, deletion, recursive cleanup |
| `Hashtable` | Linear probing, nonnegative integer keys, rehashing at half capacity, bounded searches |
| `Graph` | Linked adjacency lists; Dijkstra shortest paths, Prim minimum spanning tree, BFS components |

AVL keys are unique. The heaps and hash table retain duplicate values. The five data structures remain custom implementations; standard containers are used for temporary graph-algorithm bookkeeping.

## Tests

```bash
make test
```

Tests cover heap expansion, AVL rotations/deletion, hash collisions across resizing, graph direction symmetry and disconnected cases, real command arguments, repeated BUILD, file-only output, and errors. Optional memory checks:

```bash
make clean
make test CXXFLAGS="-std=c++11 -g -O1 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer"
```

Generated binaries and `output.txt` are excluded from Git. Editor caches are also excluded. The original coursework PDFs are omitted from this public source bundle because the technical report contains student numbers; a sanitized and updated report can be added separately.

## Original contributors

- Δέσποινα Μουκάνου
- Αριστοτέλης Κασσελούρης
