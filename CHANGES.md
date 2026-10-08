# Changes from the original repository

- Replaced literal placeholder matching with a token-based command interpreter. Filenames, numeric arguments, whitespace, and repeated BUILD now work.
- Removed eager startup construction and all console output from the application.
- Added a timed result for every executed command, including an explicit file result when an operation cannot be performed.
- Corrected hash resizing to use the new capacity and preserve all collisions and duplicates. Bounded search prevents endless probing.
- Converted the graph to the undirected representation required by the assignment, counting each edge once and deleting both adjacency entries.
- Added Dijkstra shortest-path cost, Prim spanning-tree cost, and BFS connected-component count.
- Added safe empty-AVL handling and node destruction; made ownership explicit for all five structures.
- Added file validation and nonnegative-value checks.
- Renamed Hashtaple.cpp to Hashtable.cpp, and replaced placeholders in commands.txt with usable examples.
- Added README, Makefile, .gitignore, structure tests and command integration tests.
- Removed editor cache, generated output and obsolete Replit-only configuration from the clean source package. The public-repository cleanup is performed separately by the patch instructions.

Input datasets are preserved from the current repository; they are not replaced by the slightly different ZIP datasets. Changes to Git commit email metadata are outside this source patch. Original contributor credit is preserved.
