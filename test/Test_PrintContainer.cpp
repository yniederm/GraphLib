#include <graphlib/io>

int main(int argc, char const *argv[])
{
  std::list<int> l = { 1, 2, 3, 4 };
  std::vector<int> v = { 5, 6, 7, 8 };
  std::deque<int> d = { 9, 10, 11, 12 };
  std::stack<int> s (d);

  std::cout << "std::list:\t";
  gl::io::printContainer(l);

  std::cout << "std::vector:\t";
  gl::io::printContainer(v);

  std::cout << "std::deque:\t";
  gl::io::printContainer(d);

  std::cout << "std::stack:\t";
  gl::io::printContainer(s);


  return 0;
}
