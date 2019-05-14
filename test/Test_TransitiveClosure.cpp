#include <graphlib/gl>
#include "gl_test.hpp"

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure0 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 0)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc0 {0,1,2,3,4,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,0);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc0,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure1 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 1)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc1 {0,1,2,3,4,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,1);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc1,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure2 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 2)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc2 {2,3,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,2);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc2,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure3 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 3)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc3 {2,3,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,3);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc3,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure4 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 4)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc4 {0,1,2,3,4,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,4);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc4,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure5 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 5)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc5 {5,6};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,5);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc5,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure6 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 6)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc6 {5,6};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;

  tc = gl::algorithm::transitiveClosure(g,6);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc6,1e-5)
  GL_TEST_END()
}

template <class S, class STORAGE_KIND, class D>
void TestTransitiveClosure7 ()
{
  GL_TEST_BEGIN((std::is_same_v<gl::Matrix,STORAGE_KIND> ? "Matrix" : "List") << ": Transitive closure of node " << 7)
  gl::Graph<S,STORAGE_KIND,D> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder

  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc7 {2,3,5,6,7};
  typename gl::Graph<S,STORAGE_KIND,D>::ordered_list_t tc;
  tc = gl::algorithm::transitiveClosure(g,7);
  gl::io::printContainer(tc);
  GL_NUMERIC_CONTAINER_COMPARE(tc,tc7,1e-5)
  GL_TEST_END()
}

template <class STORAGE_KIND>
void PrintGraph ()
{
  gl::Graph<int,STORAGE_KIND,gl::Directed> g(8);
  g.addEdgesFromFile("../../test/input/graph8"); // assumes running from build/test folder
  std::cout << g;
}

template <class STORAGE_KIND>
void TestRun ()
{
  PrintGraph<STORAGE_KIND>();
  TestTransitiveClosure0<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure1<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure2<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure3<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure4<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure5<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure6<int,STORAGE_KIND,gl::Directed>();
  TestTransitiveClosure7<int,STORAGE_KIND,gl::Directed>();  
}

int main(int argc, char const *argv[])
{
  TestRun<gl::Matrix>();
  TestRun<gl::List>();
  return 0;
}
