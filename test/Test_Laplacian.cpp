#include <graphlib/gl>
#include <graphlib/external>
#include <chrono>

int main(int argc, char const *argv[])
{
  gl::graphMiu g (9,"Laplacian source");
  g.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder

  auto eigen = gl::algorithm::LaplacianEigenDense(g);
  auto stl = gl::algorithm::LaplacianSTL(g);

  std::chrono::time_point< std::chrono::high_resolution_clock > t_start, t_end;
  t_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 100000; ++i)
  {
    auto eigen = gl::algorithm::LaplacianEigenDense(g);
  }

  t_end = std::chrono::high_resolution_clock::now();

  std::cout << "eigen took: " << static_cast<std::chrono::duration<double> >(t_end - t_start).count()
		        << " seconds." << std::endl;
  t_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 100000; ++i)
  {
   stl = gl::algorithm::LaplacianSTL(g);
  }

  t_end = std::chrono::high_resolution_clock::now();
  std::cout << "stl took: " << static_cast<std::chrono::duration<double> >(t_end - t_start).count()
		        << " seconds." << std::endl;

  std::cout << "Eigen Laplacian\n" << eigen << "\n\n";
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
