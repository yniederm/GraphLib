#include <graphlib/gl>
#include "gl_test.hpp"

#define GL_NUMERIC_PAIR_CONTAINER_COMPARE(Actual,Expected,AbsTol)            \
GL_ASSERT_EQUAL_DESC(Actual.size(),Expected.size(),"Container sizes")   \
{                                                                       \
  for (std::pair<typename decltype(Actual)::const_iterator,typename decltype(Expected)::const_iterator> it(Actual.cbegin(),Expected.cbegin()); it.first != Actual.cend(); ++it.first, ++it.second)        \
  {                                                                     \
    GL_ASSERT_EQUAL_ABSTOL((*(it.first)).first,(*(it.second)).first,AbsTol)             \
    GL_ASSERT_EQUAL_ABSTOL((*(it.first)).second,(*(it.second)).second,AbsTol)             \
  }                                                                     \
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestPropertyInterface (const std::string& type) {
  GL_TEST_BEGIN("Property Interface " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(4);
  g.setGraphLabel("NewLabel");
  GL_ASSERT_EQUAL_STRING(g.getGraphLabel(),"NewLabel")
  GL_ASSERT_EQUAL(g.numNodes(),4)
  GL_ASSERT_EQUAL(g.numEdges(),0)
  g.setEdge(1,2);
  g.setEdge(0,1);
  GL_ASSERT_EQUAL(g.numEdges(),2)
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestDirectedNodeDegrees (const std::string& type) {
  GL_TEST_BEGIN("Directed Node Degrees " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  gl::index_type nodeInDegree_of_0 = 1;
  gl::index_type nodeInDegree_of_1 = 3;
  gl::index_type nodeInDegree_of_2 = 1;
  gl::index_type nodeInDegree_of_3 = 0;
  gl::index_type nodeInDegree_of_4 = 1;

  gl::index_type nodeOutDegree_of_0 = 1;
  gl::index_type nodeOutDegree_of_1 = 1;
  gl::index_type nodeOutDegree_of_2 = 3;
  gl::index_type nodeOutDegree_of_3 = 1;
  gl::index_type nodeOutDegree_of_4 = 0;

  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(0),nodeInDegree_of_0,"Indegree 0")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(1),nodeInDegree_of_1,"Indegree 1")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(2),nodeInDegree_of_2,"Indegree 2")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(3),nodeInDegree_of_3,"Indegree 3")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(4),nodeInDegree_of_4,"Indegree 4")
  std::cout << "Initial Indegrees passed\n";

  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(0),nodeOutDegree_of_0,"Indegree 0")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(1),nodeOutDegree_of_1,"Outdegree 1")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(2),nodeOutDegree_of_2,"Outdegree 2")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(3),nodeOutDegree_of_3,"Outdegree 3")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(4),nodeOutDegree_of_4,"Outdegree 4")
  std::cout << "Initial Outdegrees passed\n";

  g.setEdge(2,3);
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(2),nodeOutDegree_of_2+1,"Outdegree 2")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(2),nodeInDegree_of_2,"Indegree 2")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(3),nodeOutDegree_of_3,"Outdegree 3")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(3),nodeInDegree_of_3+1,"Indegree 3")
  std::cout << "Added edge passed\n";
  g.delEdge(0,1);
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(0),nodeOutDegree_of_0-1,"Outdegree 0")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(0),nodeInDegree_of_0,"Indegree 0")
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(1),nodeOutDegree_of_1,"Outdegree 1")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(1),nodeInDegree_of_1-1,"Indegree 1")
  std::cout << "Deleted edge passed\n";
  g.delEdge(2,2);
  GL_ASSERT_EQUAL_DESC(g.getNodeOutDegree(2),nodeOutDegree_of_2,"Outdegree 2")
  GL_ASSERT_EQUAL_DESC(g.getNodeInDegree(2),nodeInDegree_of_2-1,"Indegree 2")
  std::cout << "Deleted self-loop edge passed\n";
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestUndirectedNodeDegrees (const std::string& type) {
  GL_TEST_BEGIN("Undirected Node Degrees " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  gl::index_type nodeDegree_of_0 = 2;
  gl::index_type nodeDegree_of_1 = 4;
  gl::index_type nodeDegree_of_2 = 3;
  gl::index_type nodeDegree_of_3 = 1;
  gl::index_type nodeDegree_of_4 = 1;

  GL_ASSERT_EQUAL(g.getNodeDegree(0),nodeDegree_of_0)
  GL_ASSERT_EQUAL(g.getNodeDegree(1),nodeDegree_of_1)
  GL_ASSERT_EQUAL(g.getNodeDegree(2),nodeDegree_of_2)
  GL_ASSERT_EQUAL(g.getNodeDegree(3),nodeDegree_of_3)
  GL_ASSERT_EQUAL(g.getNodeDegree(4),nodeDegree_of_4)
  std::cout << "Initial pass passed\n";
  g.setEdge(2,3);
  GL_ASSERT_EQUAL(g.getNodeDegree(2),nodeDegree_of_2+1)
  GL_ASSERT_EQUAL(g.getNodeDegree(3),nodeDegree_of_3+1)
  std::cout << "Added edge passed\n";
  g.delEdge(0,1);
  GL_ASSERT_EQUAL(g.getNodeDegree(0),nodeDegree_of_0-1)
  GL_ASSERT_EQUAL(g.getNodeDegree(1),nodeDegree_of_1-1)
  std::cout << "Deleted edge passed\n";
  g.delEdge(2,2);
  GL_ASSERT_EQUAL(g.getNodeDegree(2),nodeDegree_of_2)
  std::cout << "Deleted self-loop edge passed\n";
  GL_TEST_END()
}
template <class SCALAR, class STORAGE, class DIRECTION>
void TestNeighbours (const std::string& type) {
  GL_TEST_BEGIN("Undirected Neighbours " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  using idx_t_vector = std::vector<gl::index_type>;
  using neighbourWeightList = std::vector<std::pair<gl::index_type,SCALAR>>;

  std::vector<bool> visited {false,true,true,false,false};
  idx_t_vector neighbours_of_0;
  idx_t_vector neighbours_of_0_deleted01;
  idx_t_vector neighbours_of_1;
  idx_t_vector neighbours_of_1_deleted01;
  idx_t_vector neighbours_of_2;
  idx_t_vector neighbours_of_2_added23;
  idx_t_vector neighbours_of_2_deleted22;
  idx_t_vector neighbours_of_3;
  idx_t_vector neighbours_of_3_added23;
  idx_t_vector neighbours_of_4;

  idx_t_vector unvisited_neighbours_of_0;
  idx_t_vector unvisited_neighbours_of_0_deleted01;
  idx_t_vector unvisited_neighbours_of_1;
  idx_t_vector unvisited_neighbours_of_1_deleted01;
  idx_t_vector unvisited_neighbours_of_2;
  idx_t_vector unvisited_neighbours_of_2_added23;
  idx_t_vector unvisited_neighbours_of_2_deleted22;
  idx_t_vector unvisited_neighbours_of_3;
  idx_t_vector unvisited_neighbours_of_3_added23;
  idx_t_vector unvisited_neighbours_of_4;

  neighbourWeightList neighbourWeights_of_0;
  neighbourWeightList neighbourWeights_of_0_deleted01;
  neighbourWeightList neighbourWeights_of_1;
  neighbourWeightList neighbourWeights_of_1_deleted01;
  neighbourWeightList neighbourWeights_of_2;
  neighbourWeightList neighbourWeights_of_2_added23;
  neighbourWeightList neighbourWeights_of_2_deleted22;
  neighbourWeightList neighbourWeights_of_3;
  neighbourWeightList neighbourWeights_of_3_added23;
  neighbourWeightList neighbourWeights_of_4;

  neighbourWeightList unvisited_neighbourWeights_of_0;
  neighbourWeightList unvisited_neighbourWeights_of_0_deleted01;
  neighbourWeightList unvisited_neighbourWeights_of_1;
  neighbourWeightList unvisited_neighbourWeights_of_1_deleted01;
  neighbourWeightList unvisited_neighbourWeights_of_2;
  neighbourWeightList unvisited_neighbourWeights_of_2_added23;
  neighbourWeightList unvisited_neighbourWeights_of_2_deleted22;
  neighbourWeightList unvisited_neighbourWeights_of_3;
  neighbourWeightList unvisited_neighbourWeights_of_3_added23;
  neighbourWeightList unvisited_neighbourWeights_of_4;


  if (std::is_same_v<DIRECTION,gl::Directed>) {
    neighbours_of_0 = {1};
    neighbours_of_0_deleted01 = {};
    neighbours_of_1 = {4};
    neighbours_of_1_deleted01 = {4};
    neighbours_of_2 = {0,1,2};
    neighbours_of_2_added23 = {0,1,2,3};
    neighbours_of_2_deleted22 = {0,1,3};
    neighbours_of_3 = {1};
    neighbours_of_3_added23 = {1};
    neighbours_of_4 = {};

    unvisited_neighbours_of_0 = {};
    unvisited_neighbours_of_0_deleted01 = {};
    unvisited_neighbours_of_1 = {4};
    unvisited_neighbours_of_1_deleted01 = {4};
    unvisited_neighbours_of_2 = {0};
    unvisited_neighbours_of_2_added23 = {0,3};
    unvisited_neighbours_of_2_deleted22 = {0,3};
    unvisited_neighbours_of_3 = {};
    unvisited_neighbours_of_3_added23 = {};
    unvisited_neighbours_of_4 = {};

    neighbourWeights_of_0 = {{1,4}};
    neighbourWeights_of_0_deleted01 = {};
    neighbourWeights_of_1 = {{4,3}};
    neighbourWeights_of_1_deleted01 = {{4,3}};
    neighbourWeights_of_2 = {{0,1},{1,10},{2,5}};
    neighbourWeights_of_2_added23 = {{0,1},{1,10},{2,5},{3,1}};
    neighbourWeights_of_2_deleted22 = {{0,1},{1,10},{3,1}};
    neighbourWeights_of_3 = {{1,1}};
    neighbourWeights_of_3_added23 = {{1,1}};
    neighbourWeights_of_4 = {};

    unvisited_neighbourWeights_of_0 = {};
    unvisited_neighbourWeights_of_0_deleted01 = {};
    unvisited_neighbourWeights_of_1 = {{4,3}};
    unvisited_neighbourWeights_of_1_deleted01 = {{4,3}};
    unvisited_neighbourWeights_of_2 = {{0,1}};
    unvisited_neighbourWeights_of_2_added23 = {{0,1},{3,1}};
    unvisited_neighbourWeights_of_2_deleted22 = {{0,1},{3,1}};
    unvisited_neighbourWeights_of_3 = {};
    unvisited_neighbourWeights_of_3_added23 = {};
    unvisited_neighbourWeights_of_4 = {};
  } else 
  {
    neighbours_of_0 = {1,2};
    neighbours_of_0_deleted01 = {2};
    neighbours_of_1 = {0,2,3,4};
    neighbours_of_1_deleted01 = {2,3,4};
    neighbours_of_2 = {0,1,2};
    neighbours_of_2_added23 = {0,1,2,3};
    neighbours_of_2_deleted22 = {0,1,3};
    neighbours_of_3 = {1};
    neighbours_of_3_added23 = {1,2};
    neighbours_of_4 = {1};

    unvisited_neighbours_of_0 = {};
    unvisited_neighbours_of_0_deleted01 = {};
    unvisited_neighbours_of_1 = {0,3,4};
    unvisited_neighbours_of_1_deleted01 = {3,4};
    unvisited_neighbours_of_2 = {0};
    unvisited_neighbours_of_2_added23 = {0,3};
    unvisited_neighbours_of_2_deleted22 = {0,3};
    unvisited_neighbours_of_3 = {};
    unvisited_neighbours_of_3_added23 = {};
    unvisited_neighbours_of_4 = {};

    neighbourWeights_of_0 = {{1,4},{2,1}};
    neighbourWeights_of_0_deleted01 = {{2,1}};
    if (std::is_same_v<STORAGE,gl::Matrix>) {
      neighbourWeights_of_1 = {{0,4},{2,10},{3,1},{4,3}};
      neighbourWeights_of_1_deleted01 = {{2,10},{3,1},{4,3}};
    } else {
      neighbourWeights_of_1 = {{0,4},{3,1},{2,10},{4,3}};
      neighbourWeights_of_1_deleted01 = {{3,1},{2,10},{4,3}};
    }
    neighbourWeights_of_2 = {{0,1},{1,10},{2,5}};
    neighbourWeights_of_2_added23 = {{0,1},{1,10},{2,5},{3,1}};
    neighbourWeights_of_2_deleted22 = {{0,1},{1,10},{3,1}};
    neighbourWeights_of_3 = {{1,1}};
    neighbourWeights_of_3_added23 = {{1,1},{2,1}};
    neighbourWeights_of_4 = {{1,3}};

    unvisited_neighbourWeights_of_0 = {};
    unvisited_neighbourWeights_of_0_deleted01 = {};
    unvisited_neighbourWeights_of_1 = {{0,4},{3,1},{4,3}};
    unvisited_neighbourWeights_of_1_deleted01 = {{3,1},{4,3}};
    unvisited_neighbourWeights_of_2 = {{0,1}};
    unvisited_neighbourWeights_of_2_added23 = {{0,1},{3,1}};
    unvisited_neighbourWeights_of_2_deleted22 = {{0,1},{3,1}};
    unvisited_neighbourWeights_of_3 = {};
    unvisited_neighbourWeights_of_3_added23 = {};
    unvisited_neighbourWeights_of_4 = {};
  }

  auto n0 = g.getNeighbours(0);
  auto n1 = g.getNeighbours(1);
  auto n2 = g.getNeighbours(2);
  auto n3 = g.getNeighbours(3);
  auto n4 = g.getNeighbours(4);
  GL_NUMERIC_CONTAINER_COMPARE(n0,neighbours_of_0,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n1,neighbours_of_1,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n2,neighbours_of_2,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n3,neighbours_of_3,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n4,neighbours_of_4,1e-9)

  auto un0 = g.getUnvisitedNeighbours(0,visited);
  auto un1 = g.getUnvisitedNeighbours(1,visited);
  auto un2 = g.getUnvisitedNeighbours(2,visited);
  auto un3 = g.getUnvisitedNeighbours(3,visited);
  auto un4 = g.getUnvisitedNeighbours(4,visited);
  GL_NUMERIC_CONTAINER_COMPARE(un0,unvisited_neighbours_of_0,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un1,unvisited_neighbours_of_1,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un2,unvisited_neighbours_of_2,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un3,unvisited_neighbours_of_3,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un4,unvisited_neighbours_of_4,1e-9)

  auto nw0 = g.getNeighbourWeights(0);
  auto nw1 = g.getNeighbourWeights(1);
  auto nw2 = g.getNeighbourWeights(2);
  auto nw3 = g.getNeighbourWeights(3);
  auto nw4 = g.getNeighbourWeights(4);
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw0,neighbourWeights_of_0,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw1,neighbourWeights_of_1,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw2,neighbourWeights_of_2,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw3,neighbourWeights_of_3,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw4,neighbourWeights_of_4,1e-9)

  auto unw0 = g.getUnvisitedNeighbourWeights(0,visited);
  auto unw1 = g.getUnvisitedNeighbourWeights(1,visited);
  auto unw2 = g.getUnvisitedNeighbourWeights(2,visited);
  auto unw3 = g.getUnvisitedNeighbourWeights(3,visited);
  auto unw4 = g.getUnvisitedNeighbourWeights(4,visited);
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw0,unvisited_neighbourWeights_of_0,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw1,unvisited_neighbourWeights_of_1,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw2,unvisited_neighbourWeights_of_2,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw3,unvisited_neighbourWeights_of_3,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw4,unvisited_neighbourWeights_of_4,1e-9)
  std::cout << "Initial pass passed\n";

  g.setEdge(2,3);
  n2 = g.getNeighbours(2);
  n3 = g.getNeighbours(3);
  un2 = g.getUnvisitedNeighbours(2,visited);
  un3 = g.getUnvisitedNeighbours(3,visited);
  nw2 = g.getNeighbourWeights(2);
  nw3 = g.getNeighbourWeights(3);
  unw2 = g.getUnvisitedNeighbourWeights(2,visited);
  unw3 = g.getUnvisitedNeighbourWeights(3,visited);
  GL_NUMERIC_CONTAINER_COMPARE(n2,neighbours_of_2_added23,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n3,neighbours_of_3_added23,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un2,unvisited_neighbours_of_2_added23,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un3,unvisited_neighbours_of_3_added23,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw2,neighbourWeights_of_2_added23,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw3,neighbourWeights_of_3_added23,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw2,unvisited_neighbourWeights_of_2_added23,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw3,unvisited_neighbourWeights_of_3_added23,1e-9)
  std::cout << "Added edge passed\n";
  g.delEdge(0,1);
  n0 = g.getNeighbours(0);
  n1 = g.getNeighbours(1);
  un0 = g.getUnvisitedNeighbours(0,visited);
  un1 = g.getUnvisitedNeighbours(1,visited);
  nw0 = g.getNeighbourWeights(0);
  nw1 = g.getNeighbourWeights(1);
  unw0 = g.getUnvisitedNeighbourWeights(0,visited);
  unw1 = g.getUnvisitedNeighbourWeights(1,visited);
  GL_NUMERIC_CONTAINER_COMPARE(n0,neighbours_of_0_deleted01,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(n1,neighbours_of_1_deleted01,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un0,unvisited_neighbours_of_0_deleted01,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un1,unvisited_neighbours_of_1_deleted01,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw0,neighbourWeights_of_0_deleted01,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw1,neighbourWeights_of_1_deleted01,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw0,unvisited_neighbourWeights_of_0_deleted01,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw1,unvisited_neighbourWeights_of_1_deleted01,1e-9)
  std::cout << "Deleted edge passed\n";
  g.delEdge(2,2);
  n2 = g.getNeighbours(2);
  un2 = g.getUnvisitedNeighbours(2,visited);
  nw2 = g.getNeighbourWeights(2);
  unw2 = g.getUnvisitedNeighbourWeights(2,visited);
  GL_NUMERIC_CONTAINER_COMPARE(n2,neighbours_of_2_deleted22,1e-9)
  GL_NUMERIC_CONTAINER_COMPARE(un2,unvisited_neighbours_of_2_deleted22,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(nw2,neighbourWeights_of_2_deleted22,1e-9)
  GL_NUMERIC_PAIR_CONTAINER_COMPARE(unw2,unvisited_neighbourWeights_of_2_deleted22,1e-9)
  std::cout << "Deleted self-loop edge passed\n";
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestUpdateNode (const std::string& type) {
  GL_TEST_BEGIN("Updating Node " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  GL_ASSERT(g.getNodeColor(3) == gl::Color("white"), "Color equality")
  g.updateNode(3,"Node Three"); // label
  GL_ASSERT_EQUAL_STRING(g.getNodeLabel(3),"Node Three")
  g.updateNode(3,SCALAR(7));  // capacity
  GL_ASSERT_EQUAL(g.getNodeCapacity(3),SCALAR(7))
  g.updateNode(3,gl::Color("aqua"));  // color
  GL_ASSERT(g.getNodeColor(3) == gl::Color("aqua"), "Color equality")
  std::pair<float,float> newPos {3.2,8.2};
  g.updateNode(3,newPos);  // x/y position
  GL_ASSERT(g.getNodePosition(3) == newPos,"Position equality")

  g.updateNode(4);  // doesn't do anything
  g.updateNode(4,gl::Color("aqua"),SCALAR(7),newPos,"Node Four");
  GL_ASSERT(g.getNodeColor(4) == gl::Color("aqua"), "Color equality")
  GL_ASSERT_EQUAL_STRING(g.getNodeLabel(4),"Node Four")
  GL_ASSERT_EQUAL(g.getNodeCapacity(4),SCALAR(7))
  GL_ASSERT(g.getNodePosition(4) == newPos,"Position equality")
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestSetEdge (const std::string& type) {
  GL_TEST_BEGIN("Setting Edge " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);

  g.setEdge(0,1); // simple undirected
  GL_ASSERT_THROW(g.hasEdge(0,1))
  GL_ASSERT_EQUAL(g.getEdgeWeight(0,1),SCALAR(1))
  GL_ASSERT(g.getEdgeColor(0,1) == gl::Color("black"), "Color equality")

  g.setEdge(2,4,17,gl::Color("aqua")); // full set
  GL_ASSERT_THROW(g.hasEdge(2,4))
  GL_ASSERT_EQUAL(g.getEdgeWeight(2,4),SCALAR(17))
  GL_ASSERT(g.getEdgeColor(2,4) == gl::Color("aqua"), "Color equality")

  gl::Edge<SCALAR> e (2,3,7,gl::Color("lime"));
  g.setEdge(e); // set from edge
  GL_ASSERT_THROW(g.hasEdge(2,3))
  GL_ASSERT_EQUAL(g.getEdgeWeight(2,3),SCALAR(7))
  GL_ASSERT(g.getEdgeColor(2,3) == gl::Color("lime"), "Color equality")

  GL_TEST_CATCH_ERROR({g.setEdge(2,3);},std::runtime_error,"There is already an edge from 2 to 3")
  GL_TEST_CATCH_ERROR({g.setEdge(10,3);},std::runtime_error,"Index 10 is larger than the max: 4")

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestSetEdgesFromFile (const std::string& type) {
  GL_TEST_BEGIN("Edge Input from files " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g1 (9);
  g1.setEdgesFromListFile("../../test/input/dijkstra9");
  GL_ASSERT_EQUAL(g1.numEdges(), 14)
  GL_ASSERT(g1.hasEdge(3,4),"Edge from 3 to 4")
  GL_ASSERT_EQUAL(g1.getEdgeWeight(3,4), 9)
  std::cout << "List input succeeded" << std::endl;

  gl::Graph<SCALAR,STORAGE,DIRECTION> g2 (4);
  g2.setEdgesFromMatrixFile("../../test/input/sample_matrix");

  if (std::is_same_v<DIRECTION,gl::Directed>)
    GL_ASSERT_EQUAL(g2.numEdges(), 11)
  else 
    GL_ASSERT_EQUAL(g2.numEdges(), 9)
  GL_ASSERT(g2.hasEdge(2,3),"Edge from 2 to 3")
  GL_ASSERT_EQUAL(g2.getEdgeWeight(2,3), 6)
  std::cout << "Matrix input succeeded" << std::endl;

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestUpdateEdge (const std::string& type) {
  GL_TEST_BEGIN("Updating Edge " << type)
  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  GL_ASSERT_EQUAL(g.getEdgeWeight(3,1),SCALAR(1))
  GL_ASSERT(g.getEdgeColor(3,1) == gl::Color("black"), "Color equality")

  g.updateEdge(3,1,SCALAR(7));  // capacity
  GL_ASSERT_EQUAL(g.getEdgeWeight(3,1),SCALAR(7))
  g.updateEdge(3,1,gl::Color("red"));  // color
  GL_ASSERT(g.getEdgeColor(3,1) == gl::Color("red"), "Color equality")

  g.updateEdge(1,4);  // doesn't do anything
  g.updateEdge(1,4,gl::Color("red"),SCALAR(10));
  GL_ASSERT(g.getEdgeColor(1,4) == gl::Color("red"), "Color equality")
  GL_ASSERT_EQUAL(g.getEdgeWeight(1,4),SCALAR(10))
  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestDeleteEdge (const std::string& type) {
  GL_TEST_BEGIN("Deleting Edge " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);

  GL_ASSERT_THROW(g.hasEdge(0,1))
  GL_ASSERT_THROW(g.hasEdge(3,1))
  GL_ASSERT_THROW(g.hasEdge(2,0))
  g.delEdge(2,0);
  GL_ASSERT_THROW(g.hasEdge(0,1))
  GL_ASSERT_THROW(g.hasEdge(3,1))
  GL_ASSERT_THROW(!g.hasEdge(2,0))


  GL_TEST_CATCH_ERROR({g.delEdge(2,0);},std::runtime_error,"No edge from 2 to 0")
  GL_TEST_CATCH_ERROR({g.delEdge(10,3);},std::runtime_error,"Index 10 is larger than the max: 4")

  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestSetEdge)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestUpdateEdge)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestDeleteEdge)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestSetEdgesFromFile)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestUpdateNode)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestPropertyInterface)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestDirectedNodeDegrees,int)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestDirectedNodeDegrees,float)
  GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(TestDirectedNodeDegrees,double)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestUndirectedNodeDegrees,int)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestUndirectedNodeDegrees,float)
  GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(TestUndirectedNodeDegrees,double)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNeighbours)

  return 0;
}
