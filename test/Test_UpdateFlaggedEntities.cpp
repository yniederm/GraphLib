#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
  gl::graphLiu kruskalL(9, "Kruskal Visualized");
  kruskalL.addEdgesFromFile("test/Input_Dijkstra9"); // assumes running from project root folder

  gl::algorithm::kruskalLiu mstL5(kruskalL);

  kruskalL.readPositionsFromFile("test/dijkstra9_positions");

  gl::interface::colorFlaggedEntities(kruskalL, mstL5.EdgeSelector(gl::Color("orange")),mstL5.NodeSelector(gl::Color("lime")));

  std::ofstream out("build/test/UpdateFlaggedEntities.tex");
  gl::external::writeTikzToStream2(out, kruskalL,true);
  out.close();

  return 0;
}
