#include <graphlib/structures>
#include "gl_test.hpp"

void TestConstructor () {
  GL_TEST_BEGIN("Constructor")
  gl::Property p1;
  GL_ASSERT_EQUAL(p1.numNodes(), 0)
  GL_ASSERT_EQUAL_STRING(p1.label(), "Graph")
  GL_ASSERT_EQUAL(p1.numEdges(), 0)

  gl::Property p2(5,"Property test");
  GL_ASSERT_EQUAL(p2.numNodes(), 5)
  GL_ASSERT_EQUAL_STRING(p2.label(), "Property test")
  
  GL_TEST_END()
}

void TestUpdate () {
  GL_TEST_BEGIN("Update")

  gl::Property p1 (1,"bla bla");
  p1.numNodes(5);
  p1.label("Property test");
  p1.numEdges(27);
  GL_ASSERT_EQUAL(p1.numNodes(), 5)
  GL_ASSERT_EQUAL_STRING(p1.label(), "Property test")
  GL_ASSERT_EQUAL(p1.numEdges(), 27)


  p1.numNodesIncrement(5);
  p1.numEdgesIncrement(2);
  GL_ASSERT_EQUAL(p1.numNodes(), 10)
  GL_ASSERT_EQUAL(p1.numEdges(), 29)
  p1.numNodesDecrement(2);
  p1.numEdgesDecrement(1);
  GL_ASSERT_EQUAL(p1.numNodes(), 8)
  GL_ASSERT_EQUAL(p1.numEdges(), 28)
  GL_TEST_CATCH_ERROR(p1.numNodesDecrement(50);,std::runtime_error,"Property::numNodesDecrement | Decrement results in negative number of nodes")
  GL_TEST_CATCH_ERROR(p1.numEdgesDecrement(50);,std::runtime_error,"Property::numEdgesDecrement | Decrement results in negative number of edges")

  GL_TEST_END()
}

void TestEqualityOperator () {
  GL_TEST_BEGIN("Equality Operator")
  gl::Property p1(5,"Property test");
  gl::Property p2(5,"Property test");
  GL_ASSERT(p1 == p2, "Equality operator")
  GL_TEST_END()
}
void TestInequalityOperator () {
  GL_TEST_BEGIN("Inequality Operator")
  gl::Property p1(4,"test");
  gl::Property p2(5,"Property test");
  GL_ASSERT(p1 != p2, "Inequality operator")
  GL_TEST_END()
}
void TestCopy () {
  GL_TEST_BEGIN("Copy")
  gl::Property p1 (5,"Property test");
  gl::Property p2 (p1);
  gl::Property p3 = p1;
  GL_ASSERT_THROW(p1 == p2)
  GL_ASSERT_THROW(p1 == p3)
  GL_TEST_END()
}
void TestMove () {
  GL_TEST_BEGIN("Move")
  gl::Property p1 (5,"Property test");
  gl::Property p1_copy (5,"Property test");
  gl::Property p2 (5,"Property test");
  gl::Property p2_copy (5,"Property test");
  gl::Property p3 (std::move(p1));
  gl::Property p4 = std::move(p2);
  GL_ASSERT_THROW(p3 == p1_copy)
  GL_ASSERT_THROW(p4 == p2_copy)
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestConstructor();
  TestUpdate();
  TestEqualityOperator();
  TestInequalityOperator();
  return 0;
}
