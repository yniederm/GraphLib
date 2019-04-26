# GraphLib

A simple header-only C++ library that aims to showcase and implement various data structures and algorithms that are based on graph theory.

An up-to-date documentation of the source code is available here:

[![Documentation](https://codedocs.xyz/guetzli32/GraphLib.svg)](https://codedocs.xyz/guetzli32/GraphLib/)

# Details
## Currently implemented is the following:
### Data structures
- Graph class
  - Storage format
    - Adjacency Matrix
    - Adjacency List
    - conversion between the two
  - Directed/Undirected graphs
  - file input to add edges
  - edges & nodes support individual colours
  - edges & nodes support C++ STL conform iterators
- Initialization
  - YAML input file constructor
  - degree sequence (for undirected graphs)

### Algorithms
- Closure
  - Finding the connected component / transitive closure of a node
- DFS
  - Basic graph traversal
- BFS
  - Basic graph traversal
  - finding vertices at the same distance from source
- Minimum spanning trees
  - Kruskal
- Graph properties
  - general cycle detection
- Shortest Paths
  - Dijkstra (distances + path)
- Miscellaneous
  - Havel-Hakimi to verify whether a degree sequence is graphic

# Installation
The following software is required:
- C++17
- Cmake
- Make
- Eigen
- MathGL
- (Latex)

To build any test file, invoke `install.sh` from within the root folder of this repository. This will create executables in the `build` folder for you to run.

# To-Do list
- Document algorithm purpose in doxygen files
  
Hereafter, the term _finding <sth.>_ stands for some combination of _counting_ and _outputting <sth.>_
## Data structures
- advanced initialization 
  - stream operators
- simple graph support
- multigraph support
- bipartite graphs
- combining and editing graphs post-initialization
- threshold graphs, split graphs
## Algorithms
- BFS
  - power graphs (for undirected graphs)
- Shortest Paths
  - Floyd-Warshall
  - Bellman-Ford
  - Johnson
- Graph properties
  - cycles of specific length (e.g. triad census)
  - eccentricity, radius, diameter
- Minimum spanning trees
  - Prim
  - Total # of spanning trees
- Connectivity
  - Eulerian paths
  - finding all possible walks from source to destination
- Network algorithms
  - flow problems 
- Cliques
  - cliques of size k
- Huffman tree w/ visualization
- node things
  - centralities: 
    - degree
    - closeness
    - betweenness
    - eigenvector
    - PageRank
    - katz
- Split graph
  - find constructing degree sequence
  - computing splittance
- Bipartite graphs
  - Testing for bipartiteness
  - 2-coloring
  - vertex cover
