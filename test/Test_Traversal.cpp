#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphMiu tree(12);
  gl::graphLiu connected(10);
  tree.addEdgesFromFile("test/input/tree12"); // assumes running from project root folder
  connected.addEdgesFromFile("test/input/graph10"); // assumes running from project root folder
  gl::graphMiu::ordered_list_t tree_search;
  gl::graphLiu::ordered_list_t conn_search;

  std::cout << tree << std::endl;
  
  tree_search = gl::algorithm::DFS(tree, 0);
  std::cout << "DFS: ";
  gl::io::printContainer(tree_search);
  
  gl::algorithm::BFSMiu tree_bfs (tree, 0);
  std::cout << "BFS: ";
  gl::io::printContainer(tree_bfs.getTraversalOrder());

  std::cout << "\n" << connected << std::endl;

  conn_search = gl::algorithm::DFS(connected, 0);
  std::cout << "DFS: ";
  gl::io::printContainer(conn_search);
  
  gl::algorithm::BFSLiu conn_bfs (connected, 0);
  std::cout << "BFS Traversal order: ";
  gl::io::printContainer(conn_bfs.getTraversalOrder());

  std::cout << "\nTraversal order up to distance from 0:\n";
  for (int i = 0; i < 4; ++i) {
    std::cout << i << ": " << conn_bfs.getTraversalOrderMaxDistance(i);
  }
  std::cout << "\nNodes at fixed distances from 0:\n";
  for (int i = 0; i < 4; ++i) {
    std::cout << i << ": " << conn_bfs.getNodesExactDistance(i);
  }
  std::cout << "\nNodes up to maximum distance from 0:\n";
  for (int i = 0; i < 4; ++i) {
    std::cout << i << ": " << conn_bfs.getNodesMaxDistance(i);
  }


  return 0;
}
