#include <graphlib/gl>
#include <graphlib/external>
#include <chrono>

int main(int argc, char const *argv[])
{
  gl::graphMiu g(9, "Laplacian source");
  g.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder

  auto stl = gl::algorithm::LaplacianSTL(g);

  //gl::algorithm::PositionsFromLaplacian(stl);

  std::cout << "STL Laplacian\n";
  int i = 0;
  for (auto x : stl)
  {
    ++i;
    std::cout << (x >= 0 ? " " : "") << x << " ";
    if (i % g.numNodes() == 0)
    {
      std::cout << "\n";
      i = 0;
    }
  }

  return 0;
}
