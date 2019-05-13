#include <graphlib/io>
#include <sstream>

#include "gl_test.hpp"

void TestList ()
{
  GL_TEST_BEGIN("std::list")
  std::list<int> l = { 1, 2, 3, 4 };
  std::cout << "\t";
  gl::io::printContainer(l);

  std::stringstream ss1 ("[ 1 2 3 4 ]\n");
  std::stringstream ss2;
  ss2 << l;
  GL_ASSERT_EQUAL_STRING(ss1.str(),ss2.str())
  GL_TEST_END()
}

void TestVector ()
{
  GL_TEST_BEGIN("std::vector")
  std::vector<int> v = { 5, 6, 7, 8 };
  std::cout << "\t";
  gl::io::printContainer(v);

  std::stringstream ss1 ("[ 5 6 7 8 ]\n");
  std::stringstream ss2;
  ss2 << v;
  GL_ASSERT_EQUAL_STRING(ss1.str(),ss2.str())
  GL_TEST_END()
}

void TestDeque ()
{
  GL_TEST_BEGIN("std::deque")
  std::deque<int> d = { 9, 10, 11, 12 };
  std::cout << "\t";
  gl::io::printContainer(d);

  std::stringstream ss1 ("[ 9 10 11 12 ]\n");
  std::stringstream ss2;
  ss2 << d;
  GL_ASSERT_EQUAL_STRING(ss1.str(),ss2.str())
  GL_TEST_END()
}

void TestStack ()
{
  GL_TEST_BEGIN("std::stack")
  std::deque<int> d = { 9, 10, 11, 12 };
  std::stack<int> s (d);
  std::cout << "\t";
  gl::io::printContainer(s);

  std::stringstream ss1 ("[ 12 11 10 9 ]\n");
  std::stringstream ss2;
  ss2 << s;
  GL_ASSERT_EQUAL_STRING(ss1.str(),ss2.str())
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestList();
  TestVector();
  TestDeque();
  TestStack();

  return 0;
}
