#include <graphlib/gl>
#include "gl_test.hpp"

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSGetTraversalOrderMaxDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getTraversalOrderMaxDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(1),"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(2),"[ 0 1 2 3 4 5 6 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(3),"[ 0 1 2 3 4 5 6 7 8 9 ]\n")
  
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSGetNodesExactDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getNodesExactDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(1),"[ 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(2),"[ 4 5 6 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(3),"[ 8 9 ]\n")
  
  GL_TEST_END()
}
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSGetNodeDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getNodeDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(0),0,"0 should be 0")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(1),1,"1 should be 1")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(2),1,"2 should be 1")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(3),1,"3 should be 1")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(4),2,"4 should be 2")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(5),2,"5 should be 2")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(6),2,"6 should be 2")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(7),2,"7 should be 2")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(8),3,"8 should be 3")
  GL_ASSERT_EQUAL_DESC(bfs.getNodeDistance(9),3,"9 should be 3")
  
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSGetPathToNode (const std::string& name)
{
  GL_TEST_BEGIN("BFS getPathToNode " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(1),"[ 0 1 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(2),"[ 0 2 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(3),"[ 0 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(4),"[ 0 1 4 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(5),"[ 0 1 5 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(6),"[ 0 2 6 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(7),"[ 0 3 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getPath(8),"[ 0 1 4 8 ]\n")
  if (std::is_same_v<DIRECTION,gl::Undirected>)
  {
    GL_ASSERT_EQUAL_STREAM(bfs.getPath(9),"[ 0 1 5 9 ]\n")
  }
  if (std::is_same_v<DIRECTION,gl::Directed>)
  {
    GL_ASSERT_EQUAL_STREAM(bfs.getPath(9),"[ 0 2 6 9 ]\n")
  }
  
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSAccessBeforeInitialization (const std::string& name)
{
  GL_TEST_BEGIN("BFS Access before initialization " << name)

  gl::algorithm::BFSLiu bfs;
  GL_TEST_CATCH_ERROR(bfs.getTraversalOrder();,std::runtime_error,"BFS::getTraversalOrder | BFS has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(bfs.getTraversalOrderMaxDistance(3);,std::runtime_error,"BFS::getTraversalOrderMaxDistance | BFS has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(bfs.getNodesExactDistance(3);,std::runtime_error,"BFS::getNodesExactDistance | BFS has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(bfs.getNodeDistance(3);,std::runtime_error,"BFS::getNodeDistance | BFS has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(bfs.getNodesMaxDistance(3);,std::runtime_error,"BFS::getNodesMaxDistance | BFS has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(bfs.getPath(3);,std::runtime_error,"BFS::getPath | BFS has not been initialized with a graph.")
  GL_TEST_END()
}

void TestBFSIndexOutOfRange ()
{
  GL_TEST_BEGIN("BFS Index out of Range")
  gl::Graph<int,gl::List,gl::Directed> tree(12,"Acyclic");

  gl::algorithm::BFSLid bfs;
  bfs.compute(tree,8);
  GL_TEST_CATCH_ERROR(bfs.compute(tree, 20);,std::runtime_error,"Index 20 is larger than the max: 11")
  GL_TEST_CATCH_ERROR(bfs.getNodeDistance(20);,std::runtime_error,"Index 20 is larger than the max: 11")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSAcyclicTraversalOrder (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("BFS Acyclic Traversal Order " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> tree(12,"Acyclic");
  tree.setEdgesFromListFile("../../test/input/tree12"); // assumes running from build/test folder
  
  auto traversal = gl::algorithm::BFS(tree, 0).getTraversalOrder();
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,"[ 0 1 6 7 2 5 8 11 3 4 9 10 ]\n")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestBFSCyclicTraversalOrder (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("BFS Cyclic Traversal Order " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder
  
  auto traversal = gl::algorithm::BFS(connected, 0).getTraversalOrder();
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,"[ 0 1 2 3 4 5 6 7 8 9 ]\n")
  GL_TEST_END()
}

void TestDFSIndexOutOfRange ()
{
  GL_TEST_BEGIN("DFS Index out of Range")
  gl::Graph<int,gl::Matrix,gl::Directed> tree(12,"Acyclic");

  GL_TEST_CATCH_ERROR(gl::algorithm::DFS(tree, 20);,std::runtime_error,"Index 20 is larger than the max: 11")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestDFSAcyclic (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("DFS Acyclic " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> tree(12,"Acyclic");
  tree.setEdgesFromListFile("../../test/input/tree12"); // assumes running from build/test folder

  auto traversal = gl::algorithm::DFS(tree, 0);
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,expected)
  GL_TEST_END()
}

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void TestDFSCyclic (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("DFS Cyclic " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.setEdgesFromListFile("../../test/input/graph10"); // assumes running from build/test folder

  auto traversal = gl::algorithm::DFS(connected, 0);
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,expected)
  GL_TEST_END()
}

void TestBFSWrapper ()
{
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestBFSAccessBeforeInitialization);
  TestBFSIndexOutOfRange(); 

  std::string CyclicDirected ("[ 0 1 2 3 7 6 9 5 4 8 ]\n");
  std::string CyclicUndirected ("[ 0 1 2 3 7 6 5 4 8 9 ]\n");
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestBFSCyclicTraversalOrder,int,CyclicDirected)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestBFSCyclicTraversalOrder,int,CyclicUndirected)

  std::string AcyclicDirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  std::string AcyclicUndirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestBFSAcyclicTraversalOrder,int,AcyclicDirected)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestBFSAcyclicTraversalOrder,int,AcyclicUndirected)

  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestBFSGetTraversalOrderMaxDistance)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestBFSGetNodesExactDistance)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestBFSGetNodeDistance)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestBFSGetPathToNode)
}

void TestDFSWrapper ()
{
  TestDFSIndexOutOfRange();
  std::string CyclicDirected ("[ 0 1 2 3 7 6 9 5 4 8 ]\n");
  std::string CyclicUndirected ("[ 0 1 2 3 7 6 5 4 8 9 ]\n");
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestDFSCyclic,int,CyclicDirected)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestDFSCyclic,int,CyclicUndirected)
  std::string AcyclicDirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  std::string AcyclicUndirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestDFSAcyclic,int,AcyclicDirected)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestDFSAcyclic,int,AcyclicUndirected)
}

int main(int argc, char const *argv[])
{
  TestDFSWrapper();
  TestBFSWrapper();
  return 0;
}
