#include <graphlib/structures>
#include <graphlib/external>
#include <iostream>
#include <mgl2/mgl.h>

int main(int argc, char const *argv[])
{
    gl::graphMdd g(10);
    g.addEdgesFromFile("../../test/input/edges"); // assumes running from build/test folder
    mglGraph gr;
    gr.SetSize(1000, 1000);
    gl::external::saveImage(&gr, g, "k-"); // black lines
    gr.WritePNG("mathgl.png");
    std::cout << "saved to build/test/mathgl.png" << std::endl;
    return 0;
}
