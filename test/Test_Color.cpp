#include <vector>
#include <graphlib/gl>

void print_colors (const std::vector<gl::Color>& v) {
  for (auto& c : v) {
    printf("[%x,%x,%x,%x]\n", c.r(), c.g(), c.b(), c.a());
  }
}

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

  std::cout << colors;
  // print_colors(colors);
  
  return 0;
}

