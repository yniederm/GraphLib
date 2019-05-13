#include <graphlib/gl>
#include "gl_test.hpp"

void TestDirectedMatrixToList ()
{
  GL_TEST_BEGIN("Directed Matrix to List")
  gl::graphMdd g(4);
  g.setEdge(1,2,9.81);
  g.setEdge(2,3,-3.2);
  g.setEdge(3,0,.3);
  g.setEdge(0,3,1.2);

  gl::graphLdd expected(4);
  expected.setEdge(1,2,9.81);
  expected.setEdge(2,3,-3.2);
  expected.setEdge(3,0,.3);
  expected.setEdge(0,3,1.2);

  auto out = g.toList();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

void TestDirectedListToMatrix ()
{
  GL_TEST_BEGIN("Directed List to Matrix")
  gl::graphLdd g(4);
  g.setEdge(1,2,9.81);
  g.setEdge(2,3,-3.2);
  g.setEdge(3,0,.3);
  g.setEdge(0,3,1.2);

  gl::graphMdd expected(4);
  expected.setEdge(1,2,9.81);
  expected.setEdge(2,3,-3.2);
  expected.setEdge(3,0,.3);
  expected.setEdge(0,3,1.2);

  auto out = g.toMatrix();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

void TestUndirectedMatrixToList ()
{
  GL_TEST_BEGIN("Undirected Matrix to List")
  gl::graphMdu g(4);
  g.setEdge(0,2,5.56);
  g.setEdge(3,2,3.4);
  g.setEdge(1,1,111);
  g.setEdge(2,1,73);

  gl::graphLdu expected(4);
  expected.setEdge(0,2,5.56);
  expected.setEdge(3,2,3.4);
  expected.setEdge(1,1,111);
  expected.setEdge(2,1,73);

  auto out = g.toList();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

void TestUndirectedListToMatrix ()
{
  GL_TEST_BEGIN("Undirected List to Matrix")
  gl::graphLdu g(4);
  g.setEdge(0,2,5.56);
  g.setEdge(3,2,3.4);
  g.setEdge(1,1,111);
  g.setEdge(2,1,73);

  gl::graphMdu expected(4);
  expected.setEdge(0,2,5.56);
  expected.setEdge(3,2,3.4);
  expected.setEdge(1,1,111);
  expected.setEdge(2,1,73);

  auto out = g.toMatrix();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestDirectedMatrixToList();
  TestDirectedListToMatrix();
  TestUndirectedMatrixToList();
  TestUndirectedListToMatrix();
  return 0;
}
