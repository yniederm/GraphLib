#include <graphlib/gl>
#include "gl_test.hpp"

int main(int argc, char const *argv[])
{
  GL_TEST_INIT
  gl::graphLiu g1 ("2 4 2 1 1","Connected");
  std::cout << g1;

  gl::algorithm::floydwarshallLiu fw(g1);

  std::vector<double> cc1_actual(g1.numNodes());
  std::vector<double> cc1_expect {4./6,1.,4./6,4./7,4./7};

  std::vector<double> hc1_actual(g1.numNodes());
  std::vector<double> hc1_expect {3./4,1.,3./4,5./8,5./8};

  for (typename gl::graphLiu::idx_t i = 0; i < g1.numNodes(); ++i)
  {
    cc1_actual[i] = fw.closenessCentrality(i);
    hc1_actual[i] = fw.harmonicCentrality(i);
  }
  std::cout << "cc_connected: " << cc1_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(cc1_actual,cc1_expect,1e-9,"Closeness Centrality: Connected graph")
  std::cout << "hc_connected: " << hc1_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(hc1_actual,hc1_expect,1e-9,"Harmonic Centrality: Connected graph")

  gl::graphLiu g2 (11,"Disconnected");
  g2.setEdge(0,1);
  g2.setEdge(0,2);
  g2.setEdge(1,2);
  g2.setEdge(1,4);
  g2.setEdge(2,3);
  g2.setEdge(3,5);
  g2.setEdge(3,6);
  g2.setEdge(4,5);
  g2.setEdge(7,8);
  g2.setEdge(8,9);
  std::cout << g2;

  fw.compute(g2);
  std::vector<double> cc2_actual(g2.numNodes());
  std::vector<double> cc2_expect(g2.numNodes(),0.);

  std::vector<double> hc2_actual(g2.numNodes());
  std::vector<double> hc2_expect {(3+2./3)/10.,(4+1./3)/10.,0.45,0.45,(3.5+1./3)/10.,(3.5+1./3)/10.,0.3,0.15,0.2,0.15,0.};

  std::vector<double> idc2_actual(g2.numNodes());
  std::vector<double> idc2_expect{};
  std::vector<double> odc2_actual(g2.numNodes());
  std::vector<double> odc2_expect{};

  for (typename gl::graphLiu::idx_t i = 0; i < g2.numNodes(); ++i)
  {
    cc2_actual[i] = fw.closenessCentrality(i);
    hc2_actual[i] = fw.harmonicCentrality(i);
    idc2_actual[i] = g2.getNodeInDegree(i);
    odc2_actual[i] = g2.getNodeOutDegree(i);
  }
  std::cout << "cc_disconnected: " << cc2_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(cc2_actual,cc2_expect,1e-9,"Closeness Centrality: Disconnected graph")
  std::cout << "hc_disconnected: " << hc2_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(hc2_actual,hc2_expect,1e-9,"Harmonic Centrality: Disconnected graph")


  gl::graphMid dc_d(9, "Directed Matrix");
  gl::graphMiu dc_u(9, "Unirected Matrix");
  dc_d.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder
  dc_u.addEdgesFromFile("test/input/dijkstra9"); // assumes running from project root folder

  std::vector<double> idcd_actual(dc_d.numNodes());
  std::vector<double> idcd_expect{0,1,1,1,1,3,1,3,3};
  std::vector<double> odcd_actual(dc_d.numNodes());
  std::vector<double> odcd_expect{2,2,3,2,1,1,2,1,0};

  std::vector<double> idcu_actual(dc_u.numNodes());
  std::vector<double> odcu_actual(dc_u.numNodes());
  std::vector<double> dcu_actual(dc_d.numNodes());
  std::vector<double> dcu_expect{2,3,4,3,2,4,3,4,3};

  for (typename gl::graphMid::idx_t i = 0; i < dc_d.numNodes(); ++i)
  {
    idcd_actual[i] = dc_d.getNodeInDegree(i);
    odcd_actual[i] = dc_d.getNodeOutDegree(i);

    idcu_actual[i] = dc_u.getNodeInDegree(i);
    odcu_actual[i] = dc_u.getNodeOutDegree(i);
    dcu_actual[i] = dc_u.getNodeDegree(i);
  }
  std::cout << dc_d;
  std::cout << "idc_directed: " << idcd_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(idcd_actual,idcd_expect,1e-9,"In-Degree Centrality: Directed graph")
  std::cout << "odc_directed: " << odcd_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(odcd_actual,odcd_expect,1e-9,"Out-Degree Centrality: Directed graph")

  std::cout << dc_u;
  std::cout << "idc_undirected: " << idcu_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(idcu_actual,dcu_expect,1e-9,"In-Degree Centrality: Undirected graph")
  std::cout << "odc_undirected: " << odcu_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(odcu_actual,dcu_expect,1e-9,"Out-Degree Centrality: Undirected graph")
  std::cout << "dc_directed: " << dcu_actual;
  GL_TEST_NUMERIC_CONTAINER_COMPARE(dcu_actual,dcu_expect,1e-9,"Degree Centrality: Undirected graph")
  
  GL_TEST_TERM
  return 0;
}
