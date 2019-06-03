#include <graphlib/gl>
#include "gl_test.hpp"


template <class SCALAR, class STORAGE, class DIRECTION>
void TestCheckRange (const std::string& type) {
  GL_TEST_BEGIN("checkRange " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(4);

  GL_TEST_CATCH_ERROR(g.checkRange(5);,std::runtime_error,"Index 5 is larger than the max: 3")
  GL_TEST_CATCH_ERROR(g.checkRange(7,6);,std::runtime_error,"Index 7 is larger than the max: 3")

  GL_TEST_END()
}


template <class SCALAR, class STORAGE, class DIRECTION>
void TestEqualityOperator (const std::string& type) {
  GL_TEST_BEGIN("Equality Operator " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g1 (8,"EqualityOperator");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g2 (8,"EqualityOperator");
  g1.setEdge(2,6,78);
  g2.setEdge(2,6,78);

  GL_ASSERT(g1 == g2, "Equality Operator")

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestInequalityOperator (const std::string& type) {
  GL_TEST_BEGIN("Inequality Operator " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g1 (8,"InequalityOperator");
  gl::Graph<SCALAR,STORAGE,DIRECTION> g2 (5,"InequalityOperator");
  g1.setEdge(2,6,78);
  g2.setEdge(2,4,78);

  GL_ASSERT(g1 != g2, "Inequality Operator")

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestIsDirected (const std::string& type) {
  GL_TEST_BEGIN("IsDirected " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(3);
  bool expected = std::is_same_v<DIRECTION,gl::Directed>;
  GL_ASSERT_EQUAL(g.isDirected(),expected)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestIsUndirected (const std::string& type) {
  GL_TEST_BEGIN("IsUndirected " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(3);
  bool expected = std::is_same_v<DIRECTION,gl::Undirected>;
  GL_ASSERT_EQUAL(g.isUndirected(),expected)

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestHasCycle (const std::string& type) {
  GL_TEST_BEGIN("hasCycle " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(4);
  g.setEdge(0,1);
  g.setEdge(1,2);
  g.setEdge(2,3);
  g.setEdge(3,0);
  std::cout << g;
  GL_ASSERT_EQUAL_DESC(g.hasCycle(),true,"Should be true")

  g.delEdge(2,3);
  std::cout << g;
  GL_ASSERT_EQUAL_DESC(g.hasCycle(),false,"Should be false")

  GL_TEST_END()
}

template <class SCALAR, class STORAGE, class DIRECTION>
void TestNodeIterator (const std::string& type) {
  GL_TEST_BEGIN("Node Iterator " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  auto node_it1 = g.node_begin();
  auto node_cit1 = g.node_cbegin();

  auto node_it2 = g.node_begin();
  auto node_cit2 = g.node_cbegin();
  node_it2++;
  node_it2++;
  node_cit2++;
  node_cit2++;

  int i = 0;
  for (; node_it1 != g.node_end() && node_cit1 != g.node_cend(); ++i, ++node_it1, ++node_cit1) {
    GL_ASSERT(node_it1->id() == i,"iterator comparison")
    GL_ASSERT(node_cit1->id() == i,"const_iterator comparison")
    if (i == 2) {
    GL_ASSERT(node_it1 == node_it2, "iterator comparison at i=2")
    GL_ASSERT(node_cit1 == node_cit2, "const_iterator comparison at i=2")
    }
  }
  GL_ASSERT_EQUAL(i, g.numNodes())

  gl::Graph<SCALAR,STORAGE,DIRECTION> empty;
  for (auto it = empty.node_cbegin(); it != empty.node_cend();++it) {
    GL_ASSERT_THROW(false) // shouldn't be called
  }

  GL_TEST_END()
}
template <class SCALAR, class STORAGE, class DIRECTION>
void TestEdgeIterator (const std::string& type) {
  GL_TEST_BEGIN("Edge Iterator " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g (5);
  g.setEdge(0,1,4); // initial set
  g.setEdge(3,1);
  g.setEdge(2,0);
  g.setEdge(2,1,10);
  g.setEdge(2,2,5,gl::Color("aqua"));
  g.setEdge(1,4,3,gl::Color("orange"));

  auto edge_it1 = g.edge_begin();
  auto edge_cit1 = g.edge_cbegin();

  auto edge_it2 = g.edge_begin();
  auto edge_cit2 = g.edge_cbegin();
  edge_it2++;
  edge_it2++;
  edge_cit2++;
  edge_cit2++;

  std::vector<gl::index_type> expected_sources;
  std::vector<gl::index_type> expected_destinations;
  std::vector<SCALAR> expected_weights;
  std::vector<gl::Color> expected_colors;

  if (std::is_same_v<DIRECTION,gl::Directed>) {
    expected_sources = {0,1,2,2,2,3};
    expected_destinations = {1,4,0,1,2,1};
    expected_weights = {4,3,1,10,5,1};
    expected_colors = {gl::Color("black"),gl::Color("orange"),gl::Color("black"),gl::Color("black"),gl::Color("aqua"), gl::Color("black")};
  }
  else if (std::is_same_v<DIRECTION,gl::Undirected> && std::is_same_v<STORAGE,gl::Matrix>) {
    expected_sources = {0,0,1,1,1,2};
    expected_destinations = {1,2,2,3,4,2};
    expected_weights = {4,1,10,1,3,5};
    expected_colors = {gl::Color("black"),gl::Color("black"),gl::Color("black"),gl::Color("black"),gl::Color("orange"), gl::Color("aqua")};
  }
  else if (std::is_same_v<DIRECTION,gl::Undirected> && std::is_same_v<STORAGE,gl::List>) {
    expected_sources =      {0,0,1,1, 1,1,2, 2,2,3,4};
    expected_destinations = {1,2,0,3, 2,4,0, 1,2,1,1};
    expected_weights =      {4,1,4,1,10,3,1,10,5,1,3};
    expected_colors = {gl::Color("black"),gl::Color("black"),gl::Color("black"),gl::Color("black"),gl::Color("black"),gl::Color("orange"),gl::Color("black"),gl::Color("black"),gl::Color("aqua"),gl::Color("black"),gl::Color("orange")};
  }

  int i = 0;
  for (; edge_it1 != g.edge_end() && edge_cit1 != g.edge_cend(); ++i, ++edge_it1, ++edge_cit1) {
    std::cout << *edge_cit1 << std::endl;
    GL_ASSERT_EQUAL_DESC(edge_it1->source(),expected_sources[i],"iterator source comparison")
    GL_ASSERT_EQUAL_DESC(edge_cit1->source(), expected_sources[i],"const_iterator source comparison")
    GL_ASSERT_EQUAL_DESC(edge_it1->dest(), expected_destinations[i],"iterator dest comparison")
    GL_ASSERT_EQUAL_DESC(edge_cit1->dest(), expected_destinations[i],"const_iterator dest comparison")
    GL_ASSERT_EQUAL_DESC(edge_it1->weight(), expected_weights[i],"iterator weight comparison")
    GL_ASSERT_EQUAL_DESC(edge_cit1->weight(), expected_weights[i],"const_iterator weight comparison")
    GL_ASSERT(edge_it1->color() == expected_colors[i],"iterator color comparison")
    GL_ASSERT(edge_cit1->color() == expected_colors[i],"const_iterator color comparison")
    if (i == 2) {
    GL_ASSERT(edge_it1 == edge_it2, "iterator comparison at i=2")
    GL_ASSERT(edge_cit1 == edge_cit2, "const_iterator comparison at i=2")
    }
  }
  if (std::is_same_v<DIRECTION,gl::Undirected> && std::is_same_v<STORAGE,gl::List>) {
    GL_ASSERT_EQUAL(i, 11)
  } else
  {
    GL_ASSERT_EQUAL(i, g.numEdges())
  }
  std::cout << "before empty\n" << std::flush;
  gl::Graph<SCALAR,STORAGE,DIRECTION> empty (5);
  for (auto it = empty.edge_cbegin(); it != empty.edge_cend();++it) {
    GL_ASSERT_THROW(false) // shouldn't be called
  }
  std::cout << "after empty\n" << std::flush;

  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestCheckRange)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestEqualityOperator)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestInequalityOperator)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestIsDirected)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestIsUndirected)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestHasCycle)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestNodeIterator)
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestEdgeIterator)
  return 0;
}
