#include <graphlib/gl>
#include "gl_test.hpp"

template <class STORAGE_KIND, class DIRECTION>
void TestBFSGetTraversalOrderMaxDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getTraversalOrderMaxDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(1),"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(2),"[ 0 1 2 3 4 5 6 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getTraversalOrderMaxDistance(3),"[ 0 1 2 3 4 5 6 7 8 9 ]\n")
  
  GL_TEST_END()
}

template <class STORAGE_KIND, class DIRECTION>
void TestBFSGetNodesExactDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getNodesExactDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder

  gl::algorithm::BFS<decltype(connected)> bfs (connected,0);
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(1),"[ 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(2),"[ 4 5 6 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(bfs.getNodesExactDistance(3),"[ 8 9 ]\n")
  
  GL_TEST_END()
}
template <class STORAGE_KIND, class DIRECTION>
void TestBFSGetNodeDistance (const std::string& name)
{
  GL_TEST_BEGIN("BFS getNodeDistance " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder

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

template <class STORAGE_KIND, class DIRECTION>
void TestBFSGetPathToNode (const std::string& name)
{
  GL_TEST_BEGIN("BFS getPathToNode " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder

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

template <class STORAGE_KIND, class DIRECTION>
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

template <class STORAGE_KIND, class DIRECTION>
void TestBFSAcyclicTraversalOrder (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("BFS Acyclic Traversal Order " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> tree(12,"Acyclic");
  tree.addEdgesFromFile("../../test/input/tree12"); // assumes running from build/test folder
  
  auto traversal = gl::algorithm::BFS(tree, 0).getTraversalOrder();
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,"[ 0 1 6 7 2 5 8 11 3 4 9 10 ]\n")
  GL_TEST_END()
}

template <class STORAGE_KIND, class DIRECTION>
void TestBFSCyclicTraversalOrder (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("BFS Cyclic Traversal Order " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder
  
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

template <class STORAGE_KIND, class DIRECTION>
void TestDFSAcyclic (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("DFS Acyclic " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> tree(12,"Acyclic");
  tree.addEdgesFromFile("../../test/input/tree12"); // assumes running from build/test folder

  auto traversal = gl::algorithm::DFS(tree, 0);
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,expected)
  GL_TEST_END()
}

template <class STORAGE_KIND, class DIRECTION>
void TestDFSCyclic (const std::string& name, const std::string& expected)
{
  GL_TEST_BEGIN("DFS Cyclic " << name)
  gl::Graph<int,STORAGE_KIND,DIRECTION> connected(10,"Cyclic");
  connected.addEdgesFromFile("../../test/input/graph10"); // assumes running from build/test folder

  auto traversal = gl::algorithm::DFS(connected, 0);
  std::cout << traversal;

  GL_ASSERT_EQUAL_STREAM(traversal,expected)
  GL_TEST_END()
}

void TestBFSWrapper ()
{
  // TODO: All type macro
  std::string md ("Matrix Directed ");  
  std::string mu ("Matrix Undirected ");  
  std::string ld ("List Directed "); 
  std::string lu ("List Undirected ");
  TestBFSAccessBeforeInitialization<gl::Matrix,gl::Directed>(md);
  TestBFSAccessBeforeInitialization<gl::Matrix,gl::Undirected>(mu);
  TestBFSAccessBeforeInitialization<gl::List,gl::Directed>(ld);
  TestBFSAccessBeforeInitialization<gl::List,gl::Undirected>(lu);
  TestBFSIndexOutOfRange(); 
  std::string CyclicDirected ("[ 0 1 2 3 7 6 9 5 4 8 ]\n");
  std::string CyclicUndirected ("[ 0 1 2 3 7 6 5 4 8 9 ]\n");
  TestBFSCyclicTraversalOrder<gl::Matrix,gl::Directed>(md,CyclicDirected);
  TestBFSCyclicTraversalOrder<gl::Matrix,gl::Undirected>(mu,CyclicUndirected);
  TestBFSCyclicTraversalOrder<gl::List,gl::Directed>(ld,CyclicDirected);
  TestBFSCyclicTraversalOrder<gl::List,gl::Undirected>(lu,CyclicUndirected);
  std::string AcyclicDirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  std::string AcyclicUndirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  TestBFSAcyclicTraversalOrder<gl::Matrix,gl::Directed>(md,AcyclicDirected);
  TestBFSAcyclicTraversalOrder<gl::Matrix,gl::Undirected>(mu,AcyclicUndirected);
  TestBFSAcyclicTraversalOrder<gl::List,gl::Directed>(ld,AcyclicDirected);
  TestBFSAcyclicTraversalOrder<gl::List,gl::Undirected>(lu,AcyclicUndirected);
  TestBFSGetTraversalOrderMaxDistance<gl::Matrix,gl::Directed>(md);
  TestBFSGetTraversalOrderMaxDistance<gl::Matrix,gl::Undirected>(mu);
  TestBFSGetTraversalOrderMaxDistance<gl::List,gl::Directed>(ld);
  TestBFSGetTraversalOrderMaxDistance<gl::List,gl::Undirected>(lu);
  TestBFSGetNodesExactDistance<gl::List,gl::Undirected>(lu);
  TestBFSGetNodesExactDistance<gl::Matrix,gl::Directed>(md);
  TestBFSGetNodesExactDistance<gl::Matrix,gl::Undirected>(mu);
  TestBFSGetNodesExactDistance<gl::List,gl::Directed>(ld);
  TestBFSGetNodeDistance<gl::List,gl::Undirected>(lu);
  TestBFSGetNodeDistance<gl::Matrix,gl::Directed>(md);
  TestBFSGetNodeDistance<gl::Matrix,gl::Undirected>(mu);
  TestBFSGetNodeDistance<gl::List,gl::Directed>(ld);
  TestBFSGetPathToNode<gl::List,gl::Undirected>(lu);
  TestBFSGetPathToNode<gl::Matrix,gl::Directed>(md);
  TestBFSGetPathToNode<gl::Matrix,gl::Undirected>(mu);
  TestBFSGetPathToNode<gl::List,gl::Directed>(ld);
}

void TestDFSWrapper ()
{
  // TODO: All type macro
  TestDFSIndexOutOfRange();
  std::string md ("Matrix Directed ");  
  std::string mu ("Matrix Undirected ");  
  std::string ld ("List Directed "); 
  std::string lu ("List Undirected "); 
  std::string CyclicDirected ("[ 0 1 2 3 7 6 9 5 4 8 ]\n");
  std::string CyclicUndirected ("[ 0 1 2 3 7 6 5 4 8 9 ]\n");
  TestDFSCyclic<gl::Matrix,gl::Directed>(md,CyclicDirected);
  TestDFSCyclic<gl::Matrix,gl::Undirected>(mu,CyclicUndirected);
  TestDFSCyclic<gl::List,gl::Directed>(ld,CyclicDirected);
  TestDFSCyclic<gl::List,gl::Undirected>(lu,CyclicUndirected);
  std::string AcyclicDirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  std::string AcyclicUndirected ("[ 0 1 2 3 4 5 6 7 8 9 10 11 ]\n");
  TestDFSAcyclic<gl::Matrix,gl::Directed>(md,AcyclicDirected);
  TestDFSAcyclic<gl::Matrix,gl::Undirected>(mu,AcyclicUndirected);
  TestDFSAcyclic<gl::List,gl::Directed>(ld,AcyclicDirected);
  TestDFSAcyclic<gl::List,gl::Undirected>(lu,AcyclicUndirected);
}


int main(int argc, char const *argv[])
{
  TestDFSWrapper();
  TestBFSWrapper();
  return 0;
}
