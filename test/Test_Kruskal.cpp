#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphLiu kruskalL(9, "Kruskal List");
  gl::graphMiu kruskalM(9, "Kruskal Matrix");
  kruskalL.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from project root folder
  kruskalM.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from project root folder

  gl::algorithm::kruskalLiu mstL5(kruskalL);
  gl::algorithm::kruskalMiu mstM5(kruskalM);

  std::cout << "\n" << kruskalL << std::endl;
  std::cout << mstL5.getMST();
  std::cout << "MST Cost: " << mstL5.getCost() << "\n";

  std::cout << "\n" << kruskalM << std::endl;
  std::cout << mstM5.getMST();
  std::cout << "MST Cost: " << mstM5.getCost() << "\n";
  return 0;
}
