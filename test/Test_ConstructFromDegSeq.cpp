#include <graphlib/gl>
#include "gl_test.hpp"

void TestNormalGraphic ()
{
  GL_TEST_BEGIN("Normal Graphic sequence")
  gl::graphMiu g1_actual("3 3 2 1 1 0");
  gl::graphMiu g1_expected(6,"Simple Undirected Graph");
  g1_expected.setEdge(0,1);
  g1_expected.setEdge(0,2);
  g1_expected.setEdge(0,3);
  g1_expected.setEdge(1,2);
  g1_expected.setEdge(1,4);
  std::cout << g1_actual;

  GL_ASSERT_EQUAL_GRAPH(g1_actual,g1_expected)
  GL_TEST_END()
}

void TestFirstNodeHasAllEdges ()
{
  GL_TEST_BEGIN("First Node has all Edges")
  gl::graphLiu g2_actual("5 1 1 1 1 1");
  gl::graphLiu g2_expected(6,"Simple Undirected Graph");
  g2_expected.setEdge(0,1);
  g2_expected.setEdge(0,2);
  g2_expected.setEdge(0,3);
  g2_expected.setEdge(0,4);
  g2_expected.setEdge(0,5);
  std::cout << g2_expected;

  GL_ASSERT_EQUAL_GRAPH(g2_actual,g2_expected)
  GL_TEST_END()
}

void TestComplexGraphic ()
{
  GL_TEST_BEGIN("Complex Graphic sequence")
  gl::graphLiu g3_actual("5 5 4 4 2 1 0 1 1 1");
  gl::graphLiu g3_expected(10,"Simple Undirected Graph");
  g3_expected.setEdge(0,1);
  g3_expected.setEdge(0,2);
  g3_expected.setEdge(0,3);
  g3_expected.setEdge(0,4);
  g3_expected.setEdge(0,5);
  g3_expected.setEdge(1,2);
  g3_expected.setEdge(1,3);
  g3_expected.setEdge(1,4);
  g3_expected.setEdge(1,7);
  g3_expected.setEdge(2,3);
  g3_expected.setEdge(2,8);
  g3_expected.setEdge(3,9);
  std::cout << g3_expected;

  GL_ASSERT_EQUAL_GRAPH(g3_actual,g3_expected)
  GL_TEST_END()
}

void TestNonGraphic ()
{
  GL_TEST_BEGIN("Non-Graphic sequence")
  GL_TEST_CATCH_ERROR(gl::graphMiu g4("1 1 1 0 0","Not graphic");,std::runtime_error,"Degree Sequence is not graphic.")
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestNormalGraphic();
  TestFirstNodeHasAllEdges();
  TestComplexGraphic();
  TestNonGraphic();
  return 0;
}
