#include <graphlib/gl>
#include "gl_test.hpp"

#include <string>
#include <queue>
#include <iomanip>

void TestStringGraphic (const std::string& name)
{
  GL_TEST_BEGIN("String Graphic [" << name << " ]")
  std::cout << std::setw(5)
            << (gl::algorithm::isGraphicSequence(name) ? "graphic" : "non-graphic") 
            << "\n";
  GL_ASSERT_EQUAL_DESC(gl::algorithm::isGraphicSequence(name),true,"Should be graphic")
  GL_TEST_END()
}

void TestStringNongraphic (const std::string& name)
{
  GL_TEST_BEGIN("String Non-graphic [" << name << " ]")
  std::cout << std::setw(5)
            << (gl::algorithm::isGraphicSequence(name) ? "graphic" : "non-graphic") 
            << "\n";
  GL_ASSERT_EQUAL_DESC(gl::algorithm::isGraphicSequence(name),false,"Should be non-graphic")
  GL_TEST_END()
}


void TestDequeGraphic (const std::deque<gl::index_type>& inp, const std::string& name)
{
  GL_TEST_BEGIN("Deque Graphic [" << name << " ]")
  std::cout << std::setw(5)
            << (gl::algorithm::havelHakimi(inp) ? "graphic" : "non-graphic") 
            << "\n";
  GL_ASSERT_EQUAL_DESC(gl::algorithm::havelHakimi(inp),true,"Should be graphic")
  GL_TEST_END()
}

void TestDequeNongraphic (const std::deque<gl::index_type>& inp, const std::string& name)
{
  GL_TEST_BEGIN("Deque Non-graphic [" << name << " ]")
  std::cout << std::setw(5)
            << (gl::algorithm::havelHakimi(inp) ? "graphic" : "non-graphic") 
            << "\n";
  GL_ASSERT_EQUAL_DESC(gl::algorithm::havelHakimi(inp),false,"Should be non-graphic")
  GL_TEST_END()
}


int main(int argc, char const *argv[])
{
  std::cout << "Expected Result:\nThe first each 4 are graphic, the last 3 are not.\n";
  std::cout << "Strings:\n";
  TestStringGraphic("3 3 2 1 1 0");
  TestStringGraphic("5 1 1 1 1 1");
  TestStringGraphic("5 5 4 4 2 1 0 1 1 1");
  TestStringGraphic("0 0 0 0 0 0");
  TestStringNongraphic("1 1 1 0 0");
  TestStringNongraphic("7 2 3 0 0 0 1");
  TestStringNongraphic("4 3 3 2 2 1");
  std::cout << "Deques:\n";
  TestDequeGraphic({3,3,2,1,1,0},"3 3 2 1 1 0");
  TestDequeGraphic({5,1,1,1,1,1},"5 1 1 1 1 1");
  TestDequeGraphic({5,5,4,4,2,1,0,1,1,1},"5 5 4 4 2 1 0 1 1 1");
  TestDequeGraphic({0,0,0,0,0,0},"0 0 0 0 0 0");
  TestDequeNongraphic({1,1,1,0,0},"1 1 1 0 0");
  TestDequeNongraphic({7,2,3,0,0,0,1},"7 2 3 0 0 0 1");
  TestDequeNongraphic({4,3,3,2,2,1},"4 3 3 2 2 1");

  return 0;
}
