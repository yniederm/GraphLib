#include <graphlib/structures>
#include <graphlib/external>
#include <iostream>
#include <mgl2/mgl.h>

int main(int argc, char const *argv[])
{
    gl::graphMdd g(10);
    g.setEdge(0, 1, 1, gl::Color("red"));
    g.setEdge(0, 3, 1, gl::Color("blue"));
    g.setEdge(2, 3, 1, gl::Color("green"));
    g.setEdge(5, 7, 1, gl::Color("teal"));
    g.setEdge(1, 9, 1, gl::Color("aqua"));
    g.setEdge(5, 3); // should default to black
    g.setEdge(6, 2, 1, gl::Color("purple"));
    g.setEdge(4, 2, 1, gl::Color("fuchsia"));
    mglGraph gr;
    gr.SetSize(1000, 1000);
    gl::external::saveImage(&gr, g, ""); // black lines
    gr.WritePNG("mathgl_colors.png");
    std::cout << "saved to build/examples/mathgl_colors.png" << std::endl;
    return 0;
}
