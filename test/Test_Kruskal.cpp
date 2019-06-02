#include <graphlib/gl>
#include "gl_test.hpp"

#include <vector>
#include <utility> // for std::pair

template <class STORAGE, class DIRECTION>
void TestEmptyConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Empty constructor " << type)
  gl::algorithm::Kruskal<gl::Graph<int,STORAGE,DIRECTION>> k;
  GL_TEST_CATCH_ERROR(k.getCost();,std::runtime_error,"Kruskal::getCost | Kruskal has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(k.getMST();,std::runtime_error,"Kruskal::getMST | Kruskal has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(k.NodeSelector();,std::runtime_error,"Kruskal::NodeSelector | Kruskal has not been initialized with a graph.")
  GL_TEST_CATCH_ERROR(k.EdgeSelector();,std::runtime_error,"Kruskal::EdgeSelector | Kruskal has not been initialized with a graph.")
  GL_TEST_END()
}

template <class STORAGE, class DIRECTION>
void TestComputeConstructor (const std::string& type)
{
  GL_TEST_BEGIN("Compute constructor " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.addEdgesFromFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Kruskal<decltype(g)> k(g);

  gl::Graph<int,STORAGE,DIRECTION> g2(4,type);
  g2.setEdge(0,1,5);
  g2.setEdge(2,3,4);
  // unconnected Graph
  GL_TEST_CATCH_ERROR(gl::algorithm::Kruskal<decltype(g2)> k(g2);,std::runtime_error,std::string(std::string("Kruskal::compute | '")+type+std::string("' is not connected.\n")))

  GL_TEST_END()
}

template <class STORAGE, class DIRECTION>
void TestGetCost (const std::string& type)
{
  GL_TEST_BEGIN("Path length " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.addEdgesFromFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Kruskal<decltype(g)> k(g);
  GL_ASSERT_EQUAL_DESC(k.getCost(),37,"MST cost should be 37")
  GL_TEST_END()
}

template <class STORAGE, class DIRECTION>
void TestGetMST (const std::string& type)
{
  GL_TEST_BEGIN("SPT Graph " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.addEdgesFromFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Kruskal<decltype(g)> k(g);

  gl::Graph<int,STORAGE,DIRECTION> k0(9,std::string(std::string("MST of ")+type));
  k0.setEdge(0,1,4);
  k0.setEdge(0,7,8);
  k0.setEdge(2,3,7);
  k0.setEdge(2,5,4);
  k0.setEdge(2,8,2);
  k0.setEdge(3,4,9);
  k0.setEdge(5,6,2);
  k0.setEdge(6,7,1);

  GL_ASSERT_EQUAL_GRAPH(k.getMST(),k0)

  GL_TEST_END()
}

template <class STORAGE, class DIRECTION>
void TestEdgeSelector (const std::string& type)
{
  GL_TEST_BEGIN("Edge Selector " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.addEdgesFromFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Kruskal<decltype(g)> k(g);
  auto edgeSel = k.EdgeSelector(gl::Color("lime"), gl::Color("pink"));

  std::pair<bool,gl::Color> truePair {true,"lime"};
  std::pair<bool,gl::Color> falsePair {false,"pink"};
  
  auto mst = k.getMST();
  for (auto edge = g.edge_cbegin(); edge != g.edge_cend(); ++edge) 
  {
    auto i = edge->source();
    auto j = edge->dest();
    auto selectedPair = edgeSel(i,j);
    bool selected = selectedPair.first;
    auto color = selectedPair.second;
    if (mst.hasEdge(i,j)) 
    {
      std::cout << edge->color()<<"\n";
      GL_ASSERT(selectedPair == truePair,std::string(std::string("(")+std::to_string(i)+std::string(",")+std::to_string(j)+std::string(") should be true and lime, but is ")+(selected ? "true" : "false")+std::string(" and ")+color.RGBA()))
    }
    else
    {
      GL_ASSERT(selectedPair == falsePair,std::string(std::string("(")+std::to_string(i)+std::string(",")+std::to_string(j)+std::string(") should be false and pink, but is ")+(selected ? "true" : "false")+std::string(" and ")+color.RGBA()))
    }
  }
  GL_TEST_END()
}

template <class STORAGE, class DIRECTION>
void TestNodeSelector (const std::string& type)
{
  GL_TEST_BEGIN("Node Selector " << type)
  gl::Graph<int,STORAGE,DIRECTION> g(9,type);
  g.addEdgesFromFile("../../test/input/dijkstra9");
  // working constructor
  gl::algorithm::Kruskal<decltype(g)> k(g);
  auto nodeSel = k.NodeSelector(gl::Color("aqua"), gl::Color("pink"));

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
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestGetCost)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestGetMST)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNodeSelector)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestEdgeSelector)

  return 0;
}
