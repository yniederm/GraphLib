#include <graphlib/gl>
#include <graphlib/external>
#include <chrono>
#include "gl_test.hpp"

template <class STORAGE_KIND, class DIRECTION>
void TestSTL(const std::string &name, std::vector<float> expected)
{
  GL_TEST_BEGIN(name)
  gl::Graph<int, STORAGE_KIND, DIRECTION> g(9, "Laplacian source");
  g.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  auto stl = gl::algorithm::LaplacianSTL(g);

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
  std::cout << std::endl;
  GL_NUMERIC_CONTAINER_COMPARE(stl, expected, 1e-6)
  GL_TEST_END()
}

void TestSTLWrapper()
{
  std::vector<float> expected_d{2, -1, 0, 0, 0, 0, 0, -1, 0,
                                0, 2, -1, 0, 0, 0, 0, -1, 0,
                                0, 0, 3, -1, 0, -1, 0, 0, -1,
                                0, 0, 0, 2, -1, -1, 0, 0, 0,
                                0, 0, 0, 0, 1, -1, 0, 0, 0,
                                0, 0, 0, 0, 0, 1, -1, 0, 0,
                                0, 0, 0, 0, 0, 0, 2, -1, -1,
                                0, 0, 0, 0, 0, 0, 0, 1, -1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<float> expected_u{2, -1, 0, 0, 0, 0, 0, -1, 0,
                                -1, 3, -1, 0, 0, 0, 0, -1, 0,
                                0, -1, 4, -1, 0, -1, 0, 0, -1,
                                0, 0, -1, 3, -1, -1, 0, 0, 0,
                                0, 0, 0, -1, 2, -1, 0, 0, 0,
                                0, 0, -1, -1, -1, 4, -1, 0, 0,
                                0, 0, 0, 0, 0, -1, 3, -1, -1,
                                -1, -1, 0, 0, 0, 0, -1, 4, -1,
                                0, 0, -1, 0, 0, 0, -1, -1, 3};
  TestSTL<gl::Matrix, gl::Directed>("STL Vector: Matrix Directed", expected_d);
  TestSTL<gl::List, gl::Directed>("STL Vector: List Directed", expected_d);
  TestSTL<gl::Matrix, gl::Undirected>("STL Vector: Matrix Undirected", expected_u);
  TestSTL<gl::List, gl::Undirected>("STL Vector: List Undirected", expected_u);
}

int main(int argc, char const *argv[])
{
  TestSTLWrapper();
  return 0;
}
