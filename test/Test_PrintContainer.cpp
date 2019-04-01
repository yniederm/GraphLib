#include <graphlib/io>

int main(int argc, char const *argv[])
{
  std::list<int> l = { 7, 5, 16, 8 };
  gl::io::printContainer(l);

  
  return 0;
}
