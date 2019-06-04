#include <graphlib/gl>
#include "gl_test.hpp"

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestCyclic (const std::string& name)
{
  GL_TEST_BEGIN("hasCycle(" << name)
  gl::Graph<SCALAR,STORAGE_KIND,DIRECTION> graph(12);
  graph.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test root folder

  std::cout << (graph.hasCycle() ? "true" : "false") << "\n";
  GL_ASSERT_EQUAL(graph.hasCycle(),true)
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestAcyclic (const std::string& name)
{
  GL_TEST_BEGIN("hasCycle(" << name)
  gl::Graph<SCALAR,STORAGE_KIND,DIRECTION> graph(12);
  graph.setEdgesFromListFile("../../test/input/tree12"); // assumes running from build/test root folder

  std::cout << (graph.hasCycle() ? "true" : "false") << "\n";
  GL_ASSERT_EQUAL(graph.hasCycle(),false)
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestCyclic<double,gl::Matrix,gl::Directed>("Matrix Directed, Cyclic");
  TestCyclic<int,gl::Matrix,gl::Undirected>("Matrix Undirected, Cyclic");
  TestCyclic<double,gl::List,gl::Directed>("List Directed, Cyclic");
  TestCyclic<int,gl::List,gl::Undirected>("List Directed, Cyclic");
  TestAcyclic<double,gl::Matrix,gl::Directed>("Matrix Directed, Acyclic");
  TestAcyclic<int,gl::Matrix,gl::Undirected>("Matrix Undirected, Acyclic");
  TestAcyclic<double,gl::List,gl::Directed>("List Directed, Acyclic");
  TestAcyclic<int,gl::List,gl::Undirected>("List Directed, Acyclic");

  return 0;
}
