#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphMiu tree(12);
  gl::graphLiu cycle(10);

  tree.readFile("test/Input_tree12"); // assumes running from project root folder
  cycle.readFile("test/Input_graph10"); // assumes running from project root folder


  std::cout << "degrees(tree):         " << gl::algorithm::degrees(tree);
  std::cout << "degreeSequence(tree):  " << gl::algorithm::degreeSequence(tree);
  std::cout << "degrees(cycle):        " << gl::algorithm::degrees(cycle);
  std::cout << "degreeSequence(cycle): " << gl::algorithm::degreeSequence(cycle);

  // gl::graphMid fail(2); // This will not compile because the algorithm is only available for undirected graphs.
  // gl::algorithm::degreeSequence(fail);

  return 0;
}
