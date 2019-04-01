#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  using mgraph = gl::MGraph<int>;
  using lgraph = gl::LGraph<int>;
  mgraph tree(12);
  lgraph connected(10);
  tree.readFile("test/Input_tree12"); // assumes running from project root folder
  connected.readFile("test/Input_graph10"); // assumes running from project root folder
  mgraph::ordered_list_t tree_search;
  lgraph::ordered_list_t conn_search;

  std::cout << tree << std::endl;
  
  tree_search = gl::algorithm::DFS(tree, 0);
  std::cout << "DFS: ";
  gl::io::printContainer(tree_search);
  
  tree_search = gl::algorithm::BFS(tree, 0);
  std::cout << "BFS: ";
  gl::io::printContainer(tree_search);

  std::cout << "\n" << connected << std::endl;

  conn_search = gl::algorithm::DFS(connected, 0);
  std::cout << "DFS: ";
  gl::io::printContainer(conn_search);
  
  conn_search = gl::algorithm::BFS(connected, 0);
  std::cout << "BFS: ";
  gl::io::printContainer(conn_search);

  return 0;
}
