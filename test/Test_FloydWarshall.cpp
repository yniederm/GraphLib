#include <graphlib/gl>
#include "gl_test.hpp"

#include <vector>
#include <utility> // for std::pair

template <class SCALAR, class STORAGE, class DIRECTION>
void TestEmptyConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Empty constructor " << type)
  gl::algorithm::FloydWarshall<gl::Graph<int,STORAGE,DIRECTION>> d;
  GL_TEST_CATCH_ERROR(d.hasNegativePath();,std::runtime_error,"FloydWarshall::hasNegativePath | FloydWarshall has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.pathLength(0,3);,std::runtime_error,"FloydWarshall::pathLength | FloydWarshall has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.getPath(0,3);,std::runtime_error,"FloydWarshall::getPath | FloydWarshall has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(d.getSPT(0);,std::runtime_error,"FloydWarshall::getSPT | FloydWarshall has not been initialized with a graph.")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestComputeConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Compute constructor " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);

  // negative weight in undirected graph
  gl::Graph<int,STORAGE,gl::Undirected> g2(3,type);
  g2.setEdge(0,1,-2);
  GL_TEST_CATCH_ERROR({gl::algorithm::FloydWarshall<decltype(g2)> d2(g2);},std::runtime_error,"FloydWarshall::compute | Graph is undirected and contains negative weights")

  // negative cycles requirement check
  gl::Graph<int,STORAGE,gl::Directed> g3(3,type);
  g3.setEdge(0,1,-2);
  g3.setEdge(1,2,-1);
  g3.setEdge(2,0,-3);
  gl::algorithm::FloydWarshall<decltype(g3)> d3(g3);
  GL_ASSERT(d3.hasNegativePath(),"No negative path was detected in g3 even though there is one")
  GL_TEST_CATCH_ERROR({d3.getPath(0,1);},std::runtime_error,"FloydWarshall::getPath | The input graph has a negative cycle at node 2")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestPathLengthUndirected (const std::string& type)
{
  GL_TEST_BEGIN("Path length " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,0).scalarDistance(),0,"Path length to 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,1).scalarDistance(),4,"Path length to 1 should be 4")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,2).scalarDistance(),12,"Path length to 2 should be 12")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,3).scalarDistance(),19,"Path length to 3 should be 19")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,4).scalarDistance(),21,"Path length to 4 should be 21")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,5).scalarDistance(),11,"Path length to 5 should be 11")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,6).scalarDistance(),9,"Path length to 6 should be 9")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,7).scalarDistance(),8,"Path length to 7 should be 8")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,8).scalarDistance(),14,"Path length to 8 should be 14")
  GL_TEST_END()
}
template <class SCALAR, class STORAGE, class DIRECTION>
void TestPathLengthDirected (const std::string& type)
{
  GL_TEST_BEGIN("Path length " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,0).scalarDistance(),0,"Path length to 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,1).scalarDistance(),4,"Path length to 1 should be 4")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,2).scalarDistance(),12,"Path length to 2 should be 12")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,3).scalarDistance(),19,"Path length to 3 should be 19")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,4).scalarDistance(),28,"Path length to 4 should be 28")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,5).scalarDistance(),16,"Path length to 5 should be 16")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,6).scalarDistance(),18,"Path length to 6 should be 18")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,7).scalarDistance(),8,"Path length to 7 should be 8")
  GL_ASSERT_EQUAL_DESC(d.pathLength(0,8).scalarDistance(),14,"Path length to 8 should be 14")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetPathUndirected (const std::string& type)
{
  GL_TEST_BEGIN("Path reconstruction " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);

  GL_ASSERT_EQUAL_STREAM(d.getPath(0,0).second,"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,1).second,"[ 0 1 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,2).second,"[ 0 1 2 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,3).second,"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,4).second,"[ 0 7 6 5 4 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,5).second,"[ 0 7 6 5 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,6).second,"[ 0 7 6 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,7).second,"[ 0 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,8).second,"[ 0 1 2 8 ]\n")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetPathDirected (const std::string& type)
{
  GL_TEST_BEGIN("Path reconstruction " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);

  GL_ASSERT_EQUAL_STREAM(d.getPath(0,0).second,"[ 0 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,1).second,"[ 0 1 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,2).second,"[ 0 1 2 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,3).second,"[ 0 1 2 3 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,4).second,"[ 0 1 2 3 4 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,5).second,"[ 0 1 2 5 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,6).second,"[ 0 1 2 5 6 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,7).second,"[ 0 7 ]\n")
  GL_ASSERT_EQUAL_STREAM(d.getPath(0,8).second,"[ 0 1 2 8 ]\n")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetSPTUndirected (const std::string& type)
{
  GL_TEST_BEGIN("SPT Graph " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);

  gl::Graph<int,STORAGE,DIRECTION> g0(9,std::string(std::string("SPT of node 0 in ")+type));
  g0.setEdge(0,1,4);
  g0.setEdge(0,7,8);
  g0.setEdge(1,2,8);
  g0.setEdge(2,3,7);
  g0.setEdge(2,8,2);
  g0.setEdge(4,5,10);
  g0.setEdge(5,6,2);
  g0.setEdge(6,7,1);

  GL_ASSERT_EQUAL_GRAPH(d.getSPT(0),g0)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestGetSPTDirected (const std::string& type)
{
  GL_TEST_BEGIN("SPT Graph " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);

  gl::Graph<int,STORAGE,DIRECTION> g0(9,std::string(std::string("SPT of node 0 in ")+type));
  g0.setEdge(0,1,4);
  g0.setEdge(0,7,8);
  g0.setEdge(1,2,8);
  g0.setEdge(2,3,7);
  g0.setEdge(2,5,4);
  g0.setEdge(2,8,2);
  g0.setEdge(3,4,9);
  g0.setEdge(5,6,2);

  GL_ASSERT_EQUAL_GRAPH(d.getSPT(0),g0)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestEdgeSelector (const std::string& type)
{
  GL_TEST_BEGIN("Edge Selector " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.setEdgesFromListFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::FloydWarshall<decltype(g)> d(g);
  auto edgeSel = gl::interface::getEdgeSelectorFromShortestPathTree(d,0,gl::Color("lime"), gl::Color("pink"));

  std::pair<bool,gl::Color> truePair {true,"lime"};
  std::pair<bool,gl::Color> falsePair {false,"pink"};
  
  auto spt = d.getSPT(0);
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
  g.delEdge(3,4);
  g.delEdge(4,5);
  gl::algorithm::FloydWarshall<decltype(g)> d(g);
  auto nodeSel = gl::interface::getNodeSelectorFromShortestPathTree(d,0,gl::Color("aqua"), gl::Color("pink"));

  std::pair<bool,gl::Color> truePair {true,gl::Color("aqua")};
  std::pair<bool,gl::Color> falsePair {false,gl::Color("pink")};
  for (gl::index_type i = 0; i < g.numNodes(); ++i) {
    if (i == 4) continue;
    GL_ASSERT(nodeSel(i) == truePair,std::string(std::to_string(i)+std::string(" should be true and aqua, but is ")+(nodeSel(i).first ? "true" : "false")+std::string(" and ")+nodeSel(i).second.RGBA()))
  }
  GL_ASSERT(nodeSel(4) == falsePair,std::string(std::string("10 should be false and pink, but is ")+std::to_string(nodeSel(4).first)+std::string(" and ")+nodeSel(4).second.RGBA()))

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
