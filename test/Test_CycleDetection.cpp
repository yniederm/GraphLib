#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphMiu Miu_tree(12);
  gl::graphMid Mid_tree(12);
  gl::graphMid Liu_tree(12);
  gl::graphMid Lid_tree(12);

  gl::graphLiu Miu_cycle(10);
  gl::graphLiu Mid_cycle(10);
  gl::graphLiu Liu_cycle(10);
  gl::graphLiu Lid_cycle(10);

  Miu_tree.addEdgesFromFile("test/Input_tree12"); // assumes running from project root folder
  Mid_tree.addEdgesFromFile("test/Input_tree12"); // assumes running from project root folder
  Liu_tree.addEdgesFromFile("test/Input_tree12"); // assumes running from project root folder
  Lid_tree.addEdgesFromFile("test/Input_tree12"); // assumes running from project root folder

  Miu_cycle.addEdgesFromFile("test/Input_graph10"); // assumes running from project root folder
  Mid_cycle.addEdgesFromFile("test/Input_graph10"); // assumes running from project root folder
  Liu_cycle.addEdgesFromFile("test/Input_graph10"); // assumes running from project root folder
  Lid_cycle.addEdgesFromFile("test/Input_graph10"); // assumes running from project root folder

  // std::cout << Miu_tree;
  std::cout << "hasCycle(Miu_tree):  " << Miu_tree.hasCycle() << "\n";
  std::cout << "hasCycle(Mid_tree):  " << Mid_tree.hasCycle() << "\n";
  std::cout << "hasCycle(Liu_tree):  " << Liu_tree.hasCycle() << "\n";
  std::cout << "hasCycle(Lid_tree):  " << Lid_tree.hasCycle() << "\n";

  std::cout << "hasCycle(Miu_cycle): " << Miu_cycle.hasCycle() << "\n";
  std::cout << "hasCycle(Mid_cycle): " << Mid_cycle.hasCycle() << "\n";
  std::cout << "hasCycle(Liu_cycle): " << Liu_cycle.hasCycle() << "\n";
  std::cout << "hasCycle(Lid_cycle): " << Lid_cycle.hasCycle() << "\n";

  return 0;
}
