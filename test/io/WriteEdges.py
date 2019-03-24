from random import randint, random

edges = 200
nodes = 100

with open("edges.txt","w") as wr:
    wr.write("#include \"../../src/structures/MatrixGraph.hpp\"\n")
    wr.write("#include \"../../src/io/WriteTikz.hpp\"\n")
    wr.write("#include <iostream>\n")

    wr.write("int main(int argc, char const *argv[]) {\n")
    wr.write("  using mgraph = gl::MGraph<double>;\n")
    wr.write("  mgraph g(%s);\n" % nodes)
    for i in range(edges):
        x = randint(0, nodes-1)
        y = randint(0, nodes-1)
        wr.write("  g.setEdge(%s, %s);\n" % (x,y))
        wr.write("  g.setEdge(%s, %s);\n" % (x,y))
    wr.write("  gl::writeTikzToStream2(std::cout, g);\n")
    wr.write("  return 0;\n")
    wr.write("}\n")