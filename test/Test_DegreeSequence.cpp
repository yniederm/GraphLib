#include <graphlib/gl>
#include "gl_test.hpp"

void TestCyclicDegrees ()
{
  GL_TEST_BEGIN("degrees(cycle)")
  gl::graphLiu cycle(10);
  cycle.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test root folder

  std::cout << gl::algorithm::degrees(cycle);

  GL_ASSERT_EQUAL_STREAM(gl::algorithm::degrees(cycle),"[ 3 4 4 3 3 4 4 2 2 3 ]\n")
  GL_TEST_END()
}

void TestCyclicDegreeSequence ()
{
  GL_TEST_BEGIN("degreeSequence(cycle)")
  gl::graphLiu cycle(10);
  cycle.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test root folder

  GL_ASSERT_EQUAL_STREAM(gl::algorithm::degreeSequence(cycle),"[ 4 4 4 4 3 3 3 3 2 2 ]\n")
  GL_TEST_END()
}

void TestAcyclicDegrees ()
{
  GL_TEST_BEGIN("degrees(tree)")
  gl::graphMiu tree(12);
  tree.setEdgesFromListFile("../../test/input/tree12"); // assumes running from build/test root folder

  std::cout << gl::algorithm::degrees(tree);

  GL_ASSERT_EQUAL_STREAM(gl::algorithm::degrees(tree),"[ 3 3 3 1 1 1 1 3 3 1 1 1 ]\n")
  GL_TEST_END()
}

void TestAcyclicDegreeSequence ()
{
  GL_TEST_BEGIN("degreeSequence(tree)")
  gl::graphMiu tree(12);
  tree.setEdgesFromListFile("../../test/input/tree12"); // assumes running from build/test root folder

  std::cout << gl::algorithm::degreeSequence(tree);

  GL_ASSERT_EQUAL_STREAM(gl::algorithm::degreeSequence(tree),"[ 3 3 3 3 3 1 1 1 1 1 1 1 ]\n")
  GL_TEST_END()
}


int main(int argc, char const *argv[])
{
  TestCyclicDegrees();
  TestCyclicDegreeSequence();
  TestAcyclicDegrees();
  TestAcyclicDegreeSequence();
  // gl::graphMid fail(2); // This will not compile because the algorithm is only available for undirected graphs.
  // gl::algorithm::degreeSequence(fail);

  return 0;
}
