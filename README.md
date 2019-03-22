# GraphLib

### A simple header-only C++ library that aims to showcase and implement various data structures and algorithms that are based on graph theory.

## Currently implemented is the following:
#### Data structures
- Graph Class
  - Adjacency Matrix
  - Adjacency List
  - conversion between the two
#### Algorithms
## To-Do list
Hereafter, the term _finding <sth.>_ stands for some combination of counting and outputting <sth.>
#### Data structures
- output stream optimization
- advanced initialization (file input, stream operators)
- simple undirected graph support
- multigraph support
- bipartite graphs
- trees (a.k.a. acyclic graphs)
- combining and editing graphs post-initialization
- threshold graphs, split graphs
#### Algorithms
- BFS
  1. basic algorithm
  2. finding vertices at the same distance from source
- DFS
- Shortest Paths
  1. Dijkstra
  2. Floyd-Warshall
  3. Bellman-Ford
  4. Johnson
  5. Betweenness centrality
- Graph cycles
  1. general cycle detection
  2. cycles of specific length (e.g. triad census)
- Minimum spanning trees
  1. Kruskal
  2. Prim
  3. Total # of spanning trees
- Connectivity
  1. finding the connected component
  2. Eulerian paths
  3. transitive closures
  4. finding all possible walks from source to destination
- Network algorithms
  1. flow problems 
- vertex degree things (to be determined)
  1. centralities (?)
- Split graph
  1. find constructing degree sequence
  2. splittance