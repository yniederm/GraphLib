#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  gl::graphLdd ldd_in(4,"ldd_in");
  ldd_in.setEdge(1,2,9.81);
  ldd_in.setEdge(2,3,-3.2);
  ldd_in.setEdge(3,0,.3);
  gl::graphMdd mdd_out = ldd_in.toMatrix();
  mdd_out.name("mdd_out");

  gl::graphMdd mdd_in(4,"mdd_in");
  mdd_in.setEdge(1,2,9.81);
  mdd_in.setEdge(2,3,-3.2);
  mdd_in.setEdge(3,0,.3);
  gl::graphLdd ldd_out = mdd_in.toList();
  ldd_out.name("ldd_out");

  gl::graphLdu ldu_in(5,"ldu_in");
  ldu_in.setEdge(0,2,5.56);
  ldu_in.setEdge(3,2,3.4);
  ldu_in.setEdge(2,1,73);
  gl::graphMdu mdu_out = ldu_in.toMatrix();
  mdu_out.name("mdu_out");

  gl::graphMdu mdu_in(5,"mdu_in");
  mdu_in.setEdge(0,2,5.56);
  mdu_in.setEdge(3,2,3.4);
  mdu_in.setEdge(2,1,73);
  gl::graphLdu ldu_out = mdu_in.toList();
  ldu_out.name("ldu_out");

  std::cout << ldd_in << mdd_out << mdd_in << ldd_out
            << ldu_in << mdu_out << mdu_in << ldu_out; 
  return 0;
}
