#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphLid l_in(4);
  l_in.setEdge(1,2,9.81);
  l_in.setEdge(2,3,-3.2);
  l_in.setEdge(3,0,.3);
  gl::graphMid m_out = l_in.toMatrix();

  gl::graphMid m_in(5);
  m_in.setEdge(0,2,5.56);
  m_in.setEdge(3,2,3.4);
  m_in.setEdge(2,1,73);
  gl::graphLid l_out = m_in.toList();

  std::cout << "l_in:\n" << l_in << std::endl; 
  std::cout << "m_out:\n" << m_out << std::endl; 
  std::cout << "m_in:\n" << m_in << std::endl; 
  std::cout << "l_out:\n" << l_out << std::endl; 
  return 0;
}
