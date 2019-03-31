#include <graphlib/algorithms>

int main(int argc, char const *argv[])
{
  using graph = gl::MGraph<int>;
  graph g(8);
  g.readFile("test/Input_graph8"); // assumes running from project root folder
  std::cout << g << std::endl;
  graph::idx_list_t tc;
  for(graph::idx_t i = 0; i < g.numNodes(); i++)
  {
    tc = gl::algorithm::transitiveClosure(g, i);
    std::cout << "Transitive Closure of " << i << ": ";
    for (auto v : tc) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
