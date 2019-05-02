#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphLiu dijkstraL(9, "Dijkstra List");
  gl::graphMiu dijkstraM(9, "Dijkstra Matrix");
  dijkstraL.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder
  dijkstraM.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder

  // dijkstraL.updateEdge(0,1,-5);  // uncomment this to test the positive weights requirement

  std::cout << "\n" << dijkstraL << std::endl;
  gl::algorithm::dijkstraLiu pathL5 (dijkstraL,0);

  std::cout << "dest\tlength\tpath" << std::endl;
  for (int i = 0; i < dijkstraL.numNodes(); ++i) {
    std::cout << i << ": " << pathL5.pathLength(i) << "\t";
    gl::io::printContainer(pathL5.getPath(i));
  }

  std::cout << "\n" << dijkstraM << std::endl;
  gl::algorithm::dijkstraMiu pathM5 (dijkstraM,0);

  std::cout << "dest\tlength\tpath" << std::endl;
  for (int i = 0; i < dijkstraM.numNodes(); ++i) {
    std::cout << i << "\t" << pathM5.pathLength(i) << "\t";
    gl::io::printContainer(pathM5.getPath(i));
  }

  std::cout << pathM5.getSPT();
  return 0;
}
