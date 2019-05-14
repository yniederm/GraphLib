#include <graphlib/gl>
#include <chrono>

int main(int argc, char const *argv[])
{
  gl::graphLid graphL(4, "Floyd-Warshall List");
  graphL.setEdge(0,2,-2);
  graphL.setEdge(1,0,4);
  graphL.setEdge(1,2,3);
  graphL.setEdge(2,3,2);
  graphL.setEdge(3,1,-1);

  std::cout << "\n" << graphL << std::endl;
  gl::algorithm::floydwarshallLid fwL(graphL);

  std::cout << "src->dest: pathLength path" << std::endl;
  for (int i = 0; i < graphL.numNodes(); ++i) {
    for (int j = 0; j < graphL.numNodes(); ++j) {
      std::cout << i << "->" << j << ": " 
                << fwL.pathLength(i,j) << "  ";
      auto path = fwL.getPath(i,j);
      if (!path.first) {
        std::cout << "No path from " << i << " to " << j << "\n";
      }
      else {
        gl::io::printContainer(path.second);
      }
    }
    std::cout << std::endl;
  }

  std::cout << fwL.getSPT(3);

  return 0;
}
