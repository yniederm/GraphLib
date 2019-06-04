#include <graphlib/gl>
#include "gl_test.hpp"

void TestConnectedClosenessCentrality()
{
  GL_TEST_BEGIN("Closeness Centrality of connected Graph")
  gl::graphLiu g1 ("2 4 2 1 1","Connected");
  std::cout << g1;

  gl::algorithm::floydwarshallLiu fw(g1);

  std::vector<double> cc1_actual(g1.numNodes());
  std::vector<double> cc1_expect {4./6,1.,4./6,4./7,4./7};

  for (typename gl::graphLiu::idx_t i = 0; i < g1.numNodes(); ++i)
  {
    cc1_actual[i] = fw.closenessCentrality(i);
  }

  std::cout << "cc_connected: " << cc1_actual;
  GL_NUMERIC_CONTAINER_COMPARE(cc1_actual,cc1_expect,1e-9)
  GL_TEST_END()
}

void TestConnectedHarmonicCentrality ()
{
  GL_TEST_BEGIN("Harmonic Centrality of connected Graph")
  gl::graphLiu g1 ("2 4 2 1 1","Connected");
  std::cout << g1;

  gl::algorithm::floydwarshallLiu fw(g1);

  std::vector<double> hc1_actual(g1.numNodes());
  std::vector<double> hc1_expect {3./4,1.,3./4,5./8,5./8};

  for (typename gl::graphLiu::idx_t i = 0; i < g1.numNodes(); ++i)
  {
    hc1_actual[i] = fw.harmonicCentrality(i);
  }
  std::cout << "hc_connected: " << hc1_actual;
  GL_NUMERIC_CONTAINER_COMPARE(hc1_actual,hc1_expect,1e-9)
  GL_TEST_END()
}

void TestDisconnectedClosenessCentrality ()
{
  GL_TEST_BEGIN("Closeness Centrality of disconnected Graph")
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

  gl::algorithm::floydwarshallLiu fw(g2);
  std::vector<double> cc2_actual(g2.numNodes());
  std::vector<double> cc2_expect(g2.numNodes(),0.);

  for (typename gl::graphLiu::idx_t i = 0; i < g2.numNodes(); ++i)
  {
    cc2_actual[i] = fw.closenessCentrality(i);
  }
  std::cout << "cc_disconnected: " << cc2_actual;
  GL_NUMERIC_CONTAINER_COMPARE(cc2_actual,cc2_expect,1e-9)
  GL_TEST_END()
}

void TestDisconnectedHarmonicCentrality ()
{
  GL_TEST_BEGIN("Harmonic Centrality of disconnected Graph")
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

  gl::algorithm::floydwarshallLiu fw(g2);

  std::vector<double> hc2_actual(g2.numNodes());
  std::vector<double> hc2_expect {(3+2./3)/10.,(4+1./3)/10.,0.45,0.45,(3.5+1./3)/10.,(3.5+1./3)/10.,0.3,0.15,0.2,0.15,0.};

  for (typename gl::graphLiu::idx_t i = 0; i < g2.numNodes(); ++i)
  {
    hc2_actual[i] = fw.harmonicCentrality(i);
  }
  std::cout << "hc_disconnected: " << hc2_actual;
  GL_NUMERIC_CONTAINER_COMPARE(hc2_actual,hc2_expect,1e-9)
  GL_TEST_END()
}

void TestDirectedInDegreeCentrality ()
{
  GL_TEST_BEGIN("In-Degree Centrality of directed Graph")
  gl::graphMid dc_d(9, "Directed Matrix");
  dc_d.setEdgesFromListFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  std::cout << dc_d;

  std::vector<double> idcd_actual(dc_d.numNodes());
  std::vector<double> idcd_expect{0,1,1,1,1,3,1,3,3};

  for (typename gl::graphMid::idx_t i = 0; i < dc_d.numNodes(); ++i)
  {
    idcd_actual[i] = dc_d.getNodeInDegree(i);
  }

  std::cout << "idc_directed: " << idcd_actual;
  GL_NUMERIC_CONTAINER_COMPARE(idcd_actual,idcd_expect,1e-9)
  GL_TEST_END()
}

void TestDirectedOutDegreeCentrality ()
{
  GL_TEST_BEGIN("Out-Degree Centrality of directed Graph")
  gl::graphMid dc_d(9, "Directed Matrix");
  dc_d.setEdgesFromListFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  std::cout << dc_d;

  std::vector<double> odcd_actual(dc_d.numNodes());
  std::vector<double> odcd_expect{2,2,3,2,1,1,2,1,0};
  for (typename gl::graphMid::idx_t i = 0; i < dc_d.numNodes(); ++i)
  {
    odcd_actual[i] = dc_d.getNodeOutDegree(i);
  }

  std::cout << "odc_directed: " << odcd_actual;
  GL_NUMERIC_CONTAINER_COMPARE(odcd_actual,odcd_expect,1e-9)
  GL_TEST_END()
}


void TestUndirectedInDegreeCentrality ()
{
  GL_TEST_BEGIN("In-Degree Centrality of undirected Graph")
  gl::graphMiu dc_u(9, "Unirected Matrix");
  dc_u.setEdgesFromListFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  std::cout << dc_u;

  std::vector<double> idcu_actual(dc_u.numNodes());
  std::vector<double> idcu_expect{2,3,4,3,2,4,3,4,3};

  for (typename gl::graphMid::idx_t i = 0; i < dc_u.numNodes(); ++i)
  {
    idcu_actual[i] = dc_u.getNodeInDegree(i);
  }
  std::cout << "idc_undirected: " << idcu_actual;
  GL_NUMERIC_CONTAINER_COMPARE(idcu_actual,idcu_expect,1e-9)
  GL_TEST_END()
}
void TestUndirectedOutDegreeCentrality ()
{
  GL_TEST_BEGIN("Out-Degree Centrality of undirected Graph")
  gl::graphMiu dc_u(9, "Undirected Matrix");
  dc_u.setEdgesFromListFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  std::cout << dc_u;

  std::vector<double> odcu_actual(dc_u.numNodes());
  std::vector<double> odcu_expect{2,3,4,3,2,4,3,4,3};

  for (typename gl::graphMid::idx_t i = 0; i < dc_u.numNodes(); ++i)
  {
    odcu_actual[i] = dc_u.getNodeOutDegree(i);
  }
  std::cout << "odc_undirected: " << odcu_actual;
  GL_NUMERIC_CONTAINER_COMPARE(odcu_actual,odcu_expect,1e-9)
  GL_TEST_END()
}
void TestUndirectedDegreeCentrality ()
{
  GL_TEST_BEGIN("Degree Centrality of undirected Graph")
  gl::graphMiu dc_u(9, "Undirected Matrix");
  dc_u.setEdgesFromListFile("../../test/input/dijkstra9"); // assumes running from build/test folder
  std::cout << dc_u;

  std::vector<double> dcu_actual(dc_u.numNodes());
  std::vector<double> dcu_expect{2,3,4,3,2,4,3,4,3};

  for (typename gl::graphMid::idx_t i = 0; i < dc_u.numNodes(); ++i)
  {
    dcu_actual[i] = dc_u.getNodeDegree(i);
  }
  std::cout << "dc_directed: " << dcu_actual;
  GL_NUMERIC_CONTAINER_COMPARE(dcu_actual,dcu_expect,1e-9)
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestConnectedClosenessCentrality();
  TestConnectedHarmonicCentrality();
  TestDisconnectedClosenessCentrality();
  TestDisconnectedHarmonicCentrality();
  TestDirectedOutDegreeCentrality();
  TestDirectedInDegreeCentrality();
  TestUndirectedInDegreeCentrality(); 
  TestUndirectedOutDegreeCentrality(); 
  TestUndirectedDegreeCentrality(); 
  return 0;
}
