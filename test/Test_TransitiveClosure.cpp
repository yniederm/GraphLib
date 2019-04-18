#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphMid g(8);
  g.addEdgesFromFile("test/Input_graph8"); // assumes running from project root folder
  std::cout << g << std::endl;
  gl::graphMid::ordered_list_t tc;
  std::cout << "Transitive closure of every node:\n";
  for(gl::graphMid::idx_t i = 0; i < g.numNodes(); i++)
  {
    tc = gl::algorithm::transitiveClosure(g, i);
    std::cout << i << ": ";
    gl::io::printContainer(tc);
  }
  return 0;
}
