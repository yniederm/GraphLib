#include <graphlib/gl>
#include "gl_test.hpp"

template <class SCALAR, class STORAGE, class DIRECTION>
void TestDefaultConstructor (const std::string& type) {
  GL_TEST_BEGIN("Default constructor " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g;
  GL_ASSERT_EQUAL(g.numNodes(),0)
  GL_ASSERT_EQUAL_STRING(g.getGraphLabel(),"Graph")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestNodeLabelConstructor (const std::string& type) {
  GL_TEST_BEGIN("Node & Label constructor " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g(5);
  GL_ASSERT_EQUAL(g.numNodes(),5)
  GL_ASSERT_EQUAL_STRING(g.getGraphLabel(),"Graph")
  gl::Graph<SCALAR,STORAGE,DIRECTION> g2(5,"TestGraph");
  GL_ASSERT_EQUAL(g2.numNodes(),5)
  GL_ASSERT_EQUAL_STRING(g2.getGraphLabel(),"TestGraph")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestNormalGraphicSequenceConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Normal Graphic sequence " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g1_actual("3 3 2 1 1 0");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g1_expected(6,"Simple Undirected Graph");
  g1_expected.setEdge(0,1);
  g1_expected.setEdge(0,2);
  g1_expected.setEdge(0,3);
  g1_expected.setEdge(1,2);
  g1_expected.setEdge(1,4);
  std::cout << g1_actual;

  GL_ASSERT_EQUAL_GRAPH(g1_actual,g1_expected)
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestFirstNodeHasAllEdgesSequenceConstructor (const std::string& type)
{
  GL_TEST_BEGIN("First Node has all edges " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g2_actual("5 1 1 1 1 1");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g2_expected(6,"Simple Undirected Graph");
  g2_expected.setEdge(0,1);
  g2_expected.setEdge(0,2);
  g2_expected.setEdge(0,3);
  g2_expected.setEdge(0,4);
  g2_expected.setEdge(0,5);
  std::cout << g2_expected;

  GL_ASSERT_EQUAL_GRAPH(g2_actual,g2_expected)
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestComplexGraphicSequenceConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Complex Graphic sequence " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g3_actual("5 5 4 4 2 1 0 1 1 1");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g3_expected(10,"Simple Undirected Graph");
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

template <class SCALAR, class STORAGE, class DIRECTION>
void TestNonGraphicSequenceConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Non-Graphic sequence " << type)
  using Graph = typename gl::Graph<SCALAR,STORAGE,DIRECTION>;
  GL_TEST_CATCH_ERROR({Graph g4("1 1 1 0 0","Not graphic");},std::runtime_error,"Degree Sequence is not graphic.")
  GL_TEST_END()
}
template <class SCALAR, class STORAGE, class DIRECTION>
void TestPropertyConstructor (const std::string& type) {
  GL_TEST_BEGIN("Property constructor " << type)
  gl::Property p (6,"P-Graph");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g(p);
  GL_ASSERT_EQUAL(g.numNodes(),6)
  GL_ASSERT_EQUAL_STRING(g.getGraphLabel(),"P-Graph")
  GL_TEST_END()
}

template <class SCALAR>
void TestDirectedMatrixToList ()
{
  GL_TEST_BEGIN(std::string(std::string("Directed Matrix to List ")+typeid(SCALAR).name()))
  gl::Graph<SCALAR,gl::Matrix,gl::Directed> g(4);
  g.setEdge(1,2,9.81);
  g.setEdge(2,3,-3.2);
  g.setEdge(3,0,.3);
  g.setEdge(0,3,1.2);

  gl::Graph<SCALAR,gl::List,gl::Directed> expected(4);
  expected.setEdge(1,2,9.81);
  expected.setEdge(2,3,-3.2);
  expected.setEdge(3,0,.3);
  expected.setEdge(0,3,1.2);

  auto out = g.toList();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

template <class SCALAR>
void TestDirectedListToMatrix ()
{
  GL_TEST_BEGIN(std::string(std::string("Directed List to Matrix ")+typeid(SCALAR).name()))
  gl::Graph<SCALAR,gl::List,gl::Directed> g(4);
  g.setEdge(1,2,9.81);
  g.setEdge(2,3,-3.2);
  g.setEdge(3,0,.3);
  g.setEdge(0,3,1.2);

  gl::Graph<SCALAR,gl::Matrix,gl::Directed> expected(4);
  expected.setEdge(1,2,9.81);
  expected.setEdge(2,3,-3.2);
  expected.setEdge(3,0,.3);
  expected.setEdge(0,3,1.2);

  auto out = g.toMatrix();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

template <class SCALAR>
void TestUndirectedMatrixToList ()
{
  GL_TEST_BEGIN(std::string(std::string("Undirected Matrix to List ")+typeid(SCALAR).name()))
  gl::Graph<SCALAR,gl::Matrix,gl::Undirected> g(4);
  g.setEdge(0,2,5.56);
  g.setEdge(3,2,3.4);
  g.setEdge(1,1,111);
  g.setEdge(2,1,73);

  gl::Graph<SCALAR,gl::List,gl::Undirected> expected(4);
  expected.setEdge(0,2,5.56);
  expected.setEdge(3,2,3.4);
  expected.setEdge(1,1,111);
  expected.setEdge(2,1,73);

  auto out = g.toList();

  GL_ASSERT_EQUAL_GRAPH(out,expected)
  std::cout << g << out;
  GL_TEST_END()
}

template <class SCALAR>
void TestUndirectedListToMatrix ()
{
  GL_TEST_BEGIN(std::string(std::string("Undirected List to Matrix ")+typeid(SCALAR).name()))
  gl::Graph<SCALAR,gl::List,gl::Undirected> g(4);
  g.setEdge(0,2,5.56);
  g.setEdge(3,2,3.4);
  g.setEdge(1,1,111);
  g.setEdge(2,1,73);

  gl::Graph<SCALAR,gl::Matrix,gl::Undirected> expected(4);
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
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestDefaultConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNodeLabelConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNormalGraphicSequenceConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestFirstNodeHasAllEdgesSequenceConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestComplexGraphicSequenceConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNonGraphicSequenceConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestPropertyConstructor)
  TestDirectedMatrixToList<int>();
  TestDirectedMatrixToList<float>();
  TestDirectedMatrixToList<double>();
  TestDirectedListToMatrix<int>();
  TestDirectedListToMatrix<float>();
  TestDirectedListToMatrix<double>();
  TestUndirectedMatrixToList<int>();
  TestUndirectedMatrixToList<float>();
  TestUndirectedMatrixToList<double>();
  TestUndirectedListToMatrix<int>();
  TestUndirectedListToMatrix<float>();
  TestUndirectedListToMatrix<double>();
  return 0;
}
