#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphMiu g1("3 3 2 1 1 0");
  gl::graphLiu g2("5 1 1 1 1 1");
  gl::graphLiu g3("5 5 4 4 2 1 0 1 1 1");

  std::cout << g1 << g2 << g3; 

  return 0;
}
