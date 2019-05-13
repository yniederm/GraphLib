#include <graphlib/gl>
#include <graphlib/external>
#include <chrono>
#include "gl_test.hpp"

template <class STORAGE_KIND, class DIRECTION>
void TestSTL (const std::string& name, std::vector<float> expected)
{
  GL_TEST_BEGIN(name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> g (9,"Laplacian source");
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
  GL_NUMERIC_CONTAINER_COMPARE(stl,expected,1e-6)
  GL_TEST_END()
}

void TestSTLWrapper ()
{
  std::vector<float> expected_d{2,-1, 0, 0, 0, 0, 0,-1, 0,
                                0, 2,-1, 0, 0, 0, 0,-1, 0,
                                0, 0, 3,-1, 0,-1, 0, 0,-1,
                                0, 0, 0, 2,-1,-1, 0, 0, 0,
                                0, 0, 0, 0, 1,-1, 0, 0, 0,
                                0, 0, 0, 0, 0, 1,-1, 0, 0,
                                0, 0, 0, 0, 0, 0, 2,-1,-1,
                                0, 0, 0, 0, 0, 0, 0, 1,-1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<float> expected_u{2,-1, 0, 0, 0, 0, 0,-1, 0,
                               -1, 3,-1, 0, 0, 0, 0,-1, 0,
                                0,-1, 4,-1, 0,-1, 0, 0,-1,
                                0, 0,-1, 3,-1,-1, 0, 0, 0,
                                0, 0, 0,-1, 2,-1, 0, 0, 0,
                                0, 0,-1,-1,-1, 4,-1, 0, 0,
                                0, 0, 0, 0, 0,-1, 3,-1,-1,
                               -1,-1, 0, 0, 0, 0,-1, 4,-1,
                                0, 0,-1, 0, 0, 0,-1,-1, 3};
  TestSTL<gl::Matrix,gl::Directed>("STL Vector: Matrix Directed",expected_d);
  TestSTL<gl::List,gl::Directed>("STL Vector: List Directed",expected_d);
  TestSTL<gl::Matrix,gl::Undirected>("STL Vector: Matrix Undirected",expected_u);
  TestSTL<gl::List,gl::Undirected>("STL Vector: List Undirected",expected_u);
}


template <class STORAGE_KIND, class DIRECTION>
void TestEigenSparse (const std::string& name, Eigen::SparseMatrix<float> expected)
{
  GL_TEST_BEGIN(name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> g (9,"Laplacian source");
  g.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  auto eigen_s = gl::algorithm::LaplacianEigenSparse(g);

  std::cout << eigen_s;
  std::cout << std::endl;
  GL_EIGEN_MATRIX_COMPARE(eigen_s,expected,1e-6)
  GL_TEST_END()
}

void TestEigenSparseWrapper ()
{
  Eigen::SparseMatrix<float> expected_d(9,9), expected_u(9,9);
  std::vector<Eigen::Triplet<float>> td{{0,0,2},{0,1,-1},{0,7,-1},
                                        {1,1,2},{1,2,-1},{1,7,-1},
                                        {2,2,3},{2,3,-1},{2,5,-1},{2,8,-1},
                                        {3,3,2},{3,4,-1},{3,5,-1},
                                        {4,4,1},{4,5,-1},
                                        {5,5,1},{5,6,-1},
                                        {6,6,2},{6,7,-1},{6,8,-1},
                                        {7,7,1},{7,8,-1}};
  std::vector<Eigen::Triplet<float>> tu{{0,0,2},{0,1,-1},{0,7,-1},
                                        {1,1,3},{1,0,-1},{1,2,-1},{1,7,-1},
                                        {2,2,4},{2,1,-1},{2,3,-1},{2,5,-1},{2,8,-1},
                                        {3,3,3},{3,2,-1},{3,4,-1},{3,5,-1},
                                        {4,4,2},{4,3,-1},{4,5,-1},
                                        {5,5,4},{5,2,-1},{5,3,-1},{5,4,-1},{5,6,-1},
                                        {6,6,3},{6,5,-1},{6,7,-1},{6,8,-1},
                                        {7,7,4},{7,0,-1},{7,1,-1},{7,6,-1},{7,8,-1},
                                        {8,8,3},{8,2,-1},{8,6,-1},{8,7,-1}};
  expected_d.setFromTriplets(td.begin(), td.end());
  expected_u.setFromTriplets(tu.begin(), tu.end());

  TestEigenSparse<gl::Matrix,gl::Directed>("Eigen Sparse: Matrix Directed",expected_d);
  TestEigenSparse<gl::List,gl::Directed>("Eigen Sparse: List Directed",expected_d);
  TestEigenSparse<gl::Matrix,gl::Undirected>("Eigen Sparse: Matrix Undirected",expected_u);
  TestEigenSparse<gl::List,gl::Undirected>("Eigen Sparse: List Undirected",expected_u);
}

template <class STORAGE_KIND, class DIRECTION>
void TestEigenDense (const std::string& name, Eigen::MatrixXf expected)
{
  GL_TEST_BEGIN(name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> g (9,"Laplacian source");
  g.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  auto eigen_d = gl::algorithm::LaplacianEigenDense(g);

  std::cout << eigen_d;
  std::cout << std::endl;
  GL_EIGEN_MATRIX_COMPARE(eigen_d,expected,1e-6)
  GL_TEST_END()
}

void TestEigenDenseWrapper ()
{
  Eigen::MatrixXf expected_d(9,9), expected_u(9,9);
  expected_d << 2,-1, 0, 0, 0, 0, 0,-1, 0,
                0, 2,-1, 0, 0, 0, 0,-1, 0,
                0, 0, 3,-1, 0,-1, 0, 0,-1,
                0, 0, 0, 2,-1,-1, 0, 0, 0,
                0, 0, 0, 0, 1,-1, 0, 0, 0,
                0, 0, 0, 0, 0, 1,-1, 0, 0,
                0, 0, 0, 0, 0, 0, 2,-1,-1,
                0, 0, 0, 0, 0, 0, 0, 1,-1,
                0, 0, 0, 0, 0, 0, 0, 0, 0;
  expected_u << 2,-1, 0, 0, 0, 0, 0,-1, 0,
               -1, 3,-1, 0, 0, 0, 0,-1, 0,
                0,-1, 4,-1, 0,-1, 0, 0,-1,
                0, 0,-1, 3,-1,-1, 0, 0, 0,
                0, 0, 0,-1, 2,-1, 0, 0, 0,
                0, 0,-1,-1,-1, 4,-1, 0, 0,
                0, 0, 0, 0, 0,-1, 3,-1,-1,
               -1,-1, 0, 0, 0, 0,-1, 4,-1,
                0, 0,-1, 0, 0, 0,-1,-1, 3;
  TestEigenDense<gl::Matrix,gl::Directed>("Eigen Dense: Matrix Directed",expected_d);
  TestEigenDense<gl::List,gl::Directed>("Eigen Dense: List Directed",expected_d);
  TestEigenDense<gl::Matrix,gl::Undirected>("Eigen Dense: Matrix Undirected",expected_u);
  TestEigenDense<gl::List,gl::Undirected>("Eigen Dense: List Undirected",expected_u);
}

int main(int argc, char const *argv[])
{
  TestSTLWrapper();
  TestEigenSparseWrapper();  
  TestEigenDenseWrapper();

  return 0;
}
