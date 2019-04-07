# GraphLib

### A simple header-only C++ library that aims to showcase and implement various data structures and algorithms that are based on graph theory.

An up-to-date documentation of the source code is available here: [![Documentation](https://codedocs.xyz/guetzli32/GraphLib.svg)](https://codedocs.xyz/guetzli32/GraphLib/)
## Currently implemented is the following:
#### Data structures
- Graph Base Class
  - Adjacency Matrix
  - Adjacency List
  - conversion between the two
  - file input to add edges
#### Algorithms
- Closure
  - Finding the connected component / transitive closure of a node
- DFS
  - Basic graph traversal
- BFS
  - Basic graph traversal
- Graph cycles
  - general cycle detection
## To-Do list
- Document algorithm purpose in doxygen files
Hereafter, the term _finding <sth.>_ stands for some combination of _counting_ and _outputting <sth.>_
#### Data structures
- advanced initialization (stream operators, input file constructor)
- simple undirected graph support
- multigraph support
- bipartite graphs
- trees (a.k.a. acyclic graphs)
- combining and editing graphs post-initialization
- threshold graphs, split graphs
#### Algorithms
- BFS
  1. finding vertices at the same distance from source
- Shortest Paths
  1. Dijkstra
  2. Floyd-Warshall
  3. Bellman-Ford
  4. Johnson
  5. Betweenness centrality
- Graph cycles
  2. cycles of specific length (e.g. triad census)
- Minimum spanning trees
  1. Kruskal
  2. Prim
  3. Total # of spanning trees
- Connectivity
  2. Eulerian paths
  3. finding all possible walks from source to destination
- Network algorithms
  1. flow problems 
- vertex degree things (to be determined)
  1. centralities (?)
- Split graph
  1. find constructing degree sequence
  2. splittance
