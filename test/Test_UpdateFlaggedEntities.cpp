#include <graphlib/gl>
#include "gl_test.hpp"

template <class SCALAR, class STORAGE, class DIRECTION>
void TestColorFlaggedEntities (const std::string& type) {
  GL_TEST_BEGIN("UpdateFlaggedEntities " << type)

  gl::Graph<SCALAR,STORAGE,DIRECTION> g(4);
  g.setEdgesFromMatrixFile("../../test/input/sample_matrix"); // assumes running from build/test folder
  g.updateNode(0,"CustomName");
  g.updateNode(3,"CustomName");

  auto edgeSelector = [g](int start, int end) -> std::pair<bool,gl::Color> {
    if (g.getEdgeWeight(start,end) <= 5) 
      return {true,gl::Color("lime")};
    else 
      return {false, gl::Color("red")};
  };
  auto nodeSelector = [g](int id) -> std::pair<bool,gl::Color> {
    if (g.getNodeLabel(id) == "CustomName") 
      return {true,gl::Color("lime")};
    else 
      return {false, gl::Color("red")};
  };

  gl::Color trueColor ("lime");
  gl::Color falseColor ("black"); // default edge color
  gl::interface::colorFlaggedEntities(g,edgeSelector,nodeSelector);
  GL_ASSERT(g.getEdgeColor(0,0) == trueColor,"Edge 0->0")
  GL_ASSERT(g.getEdgeColor(0,2) == trueColor,"Edge 0->2")
  GL_ASSERT(g.getEdgeColor(0,3) == falseColor,"Edge 0->3")
  GL_ASSERT(g.getEdgeColor(1,0) == trueColor,"Edge 1->0")
  GL_ASSERT(g.getEdgeColor(1,1) == trueColor,"Edge 1->1")
  GL_ASSERT(g.getEdgeColor(1,2) == falseColor,"Edge 1->3")
  GL_ASSERT(g.getEdgeColor(2,2) == trueColor,"Edge 2->2")
  GL_ASSERT(g.getEdgeColor(2,3) == falseColor,"Edge 2->2")
  GL_ASSERT(g.getEdgeColor(3,3) == trueColor,"Edge 3->3")

  // duplicate edges in directed graph
  if (std::is_same_v<DIRECTION,gl::Directed>) {
    GL_ASSERT(g.getEdgeColor(3,0) == falseColor,"Edge 3->0")
    GL_ASSERT(g.getEdgeColor(3,2) == trueColor,"Edge 3->2")
  }

  falseColor = {"white"}; // default node color
  GL_ASSERT(g.getNodeColor(0) == trueColor,"Node 0")
  GL_ASSERT(g.getNodeColor(1) == falseColor,"Node 1")
  GL_ASSERT(g.getNodeColor(2) == falseColor,"Node 2")
  GL_ASSERT(g.getNodeColor(3) == trueColor,"Node 3")

  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  GL_TEST_FUNCTION_WITH_ALL_TYPES(TestColorFlaggedEntities)
  return 0;
}
