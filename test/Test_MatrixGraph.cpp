#include <graphlib/gl>

int main(int argc, char const *argv[])
{

  gl::graphMid g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(1,2);   // set as simple undirected
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.numNodes();
  std::cout << "numNodes: " << g.numNodes() << std::endl
            << g << std::endl;
  g.updateEdge(1,2,5); // update via setEdge

  auto neighbours_of_2 = g.getNeighbours(2);
  auto neighbourWeights_of_2 = g.getNeighbourWeights(2);

  std::cout << "Neighbours of 2: ";
  for (auto x : neighbours_of_2) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  for (auto x : neighbourWeights_of_2) {
    std::cout << "(" << x.first << "," << x.second << ") ";
  }
  std::cout << std::endl;
  std::cout << "Degree of 2: " << g.getDegree(2) << std::endl;
  g.delEdge(2,0);   // remove edge
  g.readFile("test/Input_singleEdge"); // assumes running from build folder
  // g.setEdge(-1,2,1);  // test out of range check
  // g.setEdge(1000,2,1);
  std::cout << g << std::endl;

  return 0;
}
