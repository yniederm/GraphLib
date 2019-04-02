#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  using mgraph = gl::MGraph<int>;
  using lgraph = gl::LGraph<int>;
  mgraph tree(12);
  lgraph cycle(10);
  tree.readFile("test/Input_tree12"); // assumes running from project root folder
  cycle.readFile("test/Input_graph10"); // assumes running from project root folder

  std::cout << "hasCycle(tree):  " << tree.hasCycle() << "\n";
  std::cout << "hasCycle(cycle): " << cycle.hasCycle() << "\n";

  return 0;
}
