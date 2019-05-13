#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
  // prepare test graphs
  gl::graphLiu graph1(9,"Kruskal Minimum Spanning Tree");
  graph1.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  graph1.readPositionsFromFile("../../test/input/dijkstra9_positions");

  gl::graphMiu graph2(9,"Dijkstra Shortest Paths");
  graph2.addEdgesFromFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  graph2.readPositionsFromFile("../../test/input/dijkstra9_positions");

  // test Kruskal coloring
  gl::algorithm::kruskalLiu kruskal(graph1);
  gl::interface::colorFlaggedEntities(graph1, kruskal.EdgeSelector(gl::Color("orange")),kruskal.NodeSelector(gl::Color("lime")));

  std::ofstream outKruskal("UpdateFlaggedKruskal.tex");
  gl::external::writeTikzNetwork(outKruskal, graph1, true);
  outKruskal.close();

  // gl::io::compileLatex("UpdateFlaggedKruskal.tex");

  // test Dijkstra coloring
  gl::algorithm::dijkstraMiu dijkstra(graph2,0);
  gl::interface::colorFlaggedEntities(graph2, dijkstra.EdgeSelector(),dijkstra.NodeSelector(gl::Color("fuchsia")));

  std::ofstream outDijkstra("UpdateFlaggedDijkstra.tex");
  gl::external::writeTikzNetwork(outDijkstra, graph2, true);
  outDijkstra.close();

  // gl::io::compileLatex("UpdateFlaggedDijkstra.tex");
  
  return 0;
}
