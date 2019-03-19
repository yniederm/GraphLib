#include "AdjacencyMatrix.hpp"

int main(int argc, char const *argv[])
{
  using graph_t = gl::MGraph<int>;

  graph_t g (3);
  g.setEdge(0,1,4); // initial set
  g.setEdge(1,2);   // set as simple undirected
  g.setEdge(1,2,5); // update via setEdge
  g.setEdge(2,0);
  std::cout << g << std::endl;
  g.delEdge(2,0);   // remove edge
  // g.setEdge(5,2,1);  // test out of range check
  std::cout << g << std::endl;

  return 0;
}
