#include <vector>
#include <graphlib/gl>


int main(int argc, char const *argv[])
{
  std::vector<gl::Color> colors;
  colors.push_back(gl::Color());
  colors.push_back(gl::Color(25,56,123));
  colors.push_back(gl::Color(10,19,8));
  colors.push_back(gl::Color(0.1,0.3,0.5,0.6123));
  colors.push_back(gl::Color(-0.1,5.,12312.,1.));
  colors.push_back(gl::Color(0xF23456));
  colors.push_back(gl::Color(0xFFFFFF));
  colors.push_back(gl::Color(0x67131415));
  colors.push_back(gl::Color());
  colors.push_back(gl::Color());
  colors.push_back(gl::Color());
  colors.push_back(gl::Color("orange"));

  colors[8].hex(0x123456);
  colors[9].hex(0x78123456);
  colors[10].r(0x1);
  colors[10].g(0x2);
  colors[10].b(0x3);
  colors[10].a(0x4);

  std::cout << colors;
  
  return 0;
}

