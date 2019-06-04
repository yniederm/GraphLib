#include <graphlib/gl>
#include "gl_test.hpp"

#include <vector>
#include <utility> // for std::pair

template <class SCALAR, class STORAGE, class DIRECTION>
void TestEmptyConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Empty constructor " << type)
  gl::algorithm::Dijkstra<gl::Graph<int,STORAGE,DIRECTION>> d;
  GL_TEST_CATCH_ERROR(d.getSource();,std::runtime_error,"Dijkstra::getSource | Dijkstra has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.pathLength(3);,std::runtime_error,"Dijkstra::pathLength | Dijkstra has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.getPath(3);,std::runtime_error,"Dijkstra::getPath | Dijkstra has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.getSPT();,std::runtime_error,"Dijkstra::getSPT | Dijkstra has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.NodeSelector();,std::runtime_error,"Dijkstra::NodeSelector | Dijkstra has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.EdgeSelector();,std::runtime_error,"Dijkstra::EdgeSelector | Dijkstra has not been initialized with a graph.")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestComputeConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Compute constructor " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,7);
  GL_ASSERT_EQUAL_DESC(d.getSource(),7,"Source should be 7.")

  // source index out of range check
  GL_TEST_CATCH_ERROR({gl::algorithm::Dijkstra<decltype(g)> d2(g,9);},std::runtime_error,"Index 9 is larger than the max: 8")

  // positive weights requirement check
  g.updateEdge(0,1,-5);
  GL_TEST_CATCH_ERROR({gl::algorithm::Dijkstra<decltype(g)> d3(g,0);},std::runtime_error,"Dijkstra::compute | Found non-positive edge weights in the graph.")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestPathLengthUndirected (const std::string& type)
{
  GL_TEST_BEGIN("Path length " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);
  GL_ASSERT_EQUAL_DESC(d.pathLength(0),0,"Path length to 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.pathLength(1),4,"Path length to 1 should be 4")
  GL_ASSERT_EQUAL_DESC(d.pathLength(2),12,"Path length to 2 should be 12")
  GL_ASSERT_EQUAL_DESC(d.pathLength(3),19,"Path length to 3 should be 19")
  GL_ASSERT_EQUAL_DESC(d.pathLength(4),21,"Path length to 4 should be 21")
  GL_ASSERT_EQUAL_DESC(d.pathLength(5),11,"Path length to 5 should be 11")
  GL_ASSERT_EQUAL_DESC(d.pathLength(6),9,"Path length to 6 should be 9")
  GL_ASSERT_EQUAL_DESC(d.pathLength(7),8,"Path length to 7 should be 8")
  GL_ASSERT_EQUAL_DESC(d.pathLength(8),14,"Path length to 8 should be 14")
  GL_TEST_END()
}
template <class SCALAR, class STORAGE, class DIRECTION>
void TestPathLengthDirected (const std::string& type)
{
  GL_TEST_BEGIN("Path length " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);
  GL_ASSERT_EQUAL_DESC(d.pathLength(0),0,"Path length to 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.pathLength(1),4,"Path length to 1 should be 4")
  GL_ASSERT_EQUAL_DESC(d.pathLength(2),12,"Path length to 2 should be 12")
  GL_ASSERT_EQUAL_DESC(d.pathLength(3),19,"Path length to 3 should be 19")
  GL_ASSERT_EQUAL_DESC(d.pathLength(4),28,"Path length to 4 should be 28")
  GL_ASSERT_EQUAL_DESC(d.pathLength(5),16,"Path length to 5 should be 16")
  GL_ASSERT_EQUAL_DESC(d.pathLength(6),18,"Path length to 6 should be 18")
  GL_ASSERT_EQUAL_DESC(d.pathLength(7),8,"Path length to 7 should be 8")
  GL_ASSERT_EQUAL_DESC(d.pathLength(8),14,"Path length to 8 should be 14")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetPathUndirected (const std::string& type)
{
  GL_TEST_BEGIN("Path reconstruction " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);

  GL_ASSERT_EQUAL_STREAM(d.getPath(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(1),"[ 0 1 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(2),"[ 0 1 2 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(3),"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(4),"[ 0 7 6 5 4 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(5),"[ 0 7 6 5 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(6),"[ 0 7 6 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(7),"[ 0 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(8),"[ 0 1 2 8 ]\n")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetPathDirected (const std::string& type)
{
  GL_TEST_BEGIN("Path reconstruction " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);

  GL_ASSERT_EQUAL_STREAM(d.getPath(0),"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(1),"[ 0 1 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(2),"[ 0 1 2 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(3),"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(4),"[ 0 1 2 3 4 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(5),"[ 0 1 2 5 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(6),"[ 0 1 2 5 6 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(7),"[ 0 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(8),"[ 0 1 2 8 ]\n")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetSPTUndirected (const std::string& type)
{
  GL_TEST_BEGIN("SPT Graph " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);

  gl::Graph<int,STORAGE,DIRECTION> g0(9,std::string(std::string("SPT of node 0 in ")+type));
  g0.setEdge(0,1,4);
  g0.setEdge(0,7,8);
  g0.setEdge(1,2,8);
  g0.setEdge(2,3,7);
  g0.setEdge(2,8,2);
  g0.setEdge(4,5,10);
  g0.setEdge(5,6,2);
  g0.setEdge(6,7,1);

  GL_ASSERT_EQUAL_GRAPH(d.getSPT(),g0)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetSPTDirected (const std::string& type)
{
  GL_TEST_BEGIN("SPT Graph " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);

  gl::Graph<int,STORAGE,DIRECTION> g0(9,std::string(std::string("SPT of node 0 in ")+type));
  g0.setEdge(0,1,4);
  g0.setEdge(0,7,8);
  g0.setEdge(1,2,8);
  g0.setEdge(2,3,7);
  g0.setEdge(2,5,4);
  g0.setEdge(2,8,2);
  g0.setEdge(3,4,9);
  g0.setEdge(5,6,2);

  GL_ASSERT_EQUAL_GRAPH(d.getSPT(),g0)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestEdgeSelector (const std::string& type)
{
  GL_TEST_BEGIN("Edge Selector " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);
  auto edgeSel = d.EdgeSelector(gl::Color("lime"), gl::Color("pink"));

  std::pair<bool,gl::Color> truePair {true,"lime"};
  std::pair<bool,gl::Color> falsePair {false,"pink"};
  
  auto spt = d.getSPT();
  for (auto edge = g.edge_cbegin(); edge != g.edge_cend(); ++edge) 
  {
    auto i = edge->source();
    auto j = edge->dest();
    auto selectedPair = edgeSel(i,j);
    bool selected = selectedPair.first;
    auto color = selectedPair.second;
    if (spt.hasEdge(i,j)) 
    {
      GL_ASSERT(selectedPair == truePair,std::string(std::string("(")+std::to_string(i)+std::string(",")+std::to_string(j)+std::string(") should be true and lime, but is ")+(selected ? "true" : "false")+std::string(" and ")+color.RGBA()))
    }
    else
    {
      GL_ASSERT(selectedPair == falsePair,std::string(std::string("(")+std::to_string(i)+std::string(",")+std::to_string(j)+std::string(") should be false and pink, but is ")+(selected ? "true" : "false")+std::string(" and ")+color.RGBA()))
    }
    
  }
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestNodeSelector (const std::string& type)
{
  GL_TEST_BEGIN("Node Selector " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Dijkstra<decltype(g)> d(g,0);
  auto nodeSel = d.NodeSelector(gl::Color("aqua"), gl::Color("pink"));

  std::pair<bool,gl::Color> truePair {true,gl::Color("aqua")};
  std::pair<bool,gl::Color> falsePair {false,gl::Color("pink")};
  for (gl::index_type i = 0; i < g.numNodes(); ++i) {
    GL_ASSERT(nodeSel(i) == truePair,std::string(std::to_string(i)+std::string(" should be true and aqua, but is ")+(nodeSel(i).first ? "true" : "false")+std::string(" and ")+nodeSel(i).second.RGBA()))
  }
  GL_ASSERT(nodeSel(10) == falsePair,std::string(std::string("10 should be false and pink, but is ")+std::to_string(nodeSel(10).first)+std::string(" and ")+nodeSel(10).second.RGBA()))

  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestEmptyConstructor)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestComputeConstructor)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestPathLengthUndirected,int)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestPathLengthDirected,int)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestGetPathUndirected,int)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestGetPathDirected,int)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestGetSPTUndirected,int)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestGetSPTDirected,int)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNodeSelector)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestEdgeSelector)

  return 0;
}
