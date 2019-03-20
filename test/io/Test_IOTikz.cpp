#include "../../src/structures/MatrixGraph.hpp"
#include "../../src/io/WriteTikz.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    using mgraph = gl::MGraph<double>;

    mgraph g(3);
    g.setEdge(0, 1, 1);
    g.setEdge(1, 2, 2);
    g.setEdge(2, 1, 3);
    g.setEdge(1, 0, 4);
    g.setEdge(0, 0, 5);
    g.setEdge(2, 2, 6);
    g.setEdge(0, 2, 7);
    g.setEdge(2, 0, 8);

    gl::writeTikzToStream(std::cout, g);

    return 0;
}
