#include <iostream>
#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("test/input/switzerland.yml");

    gl::graphMdu g = *std::get<gl::graphMdu *>(reader.get());

    gl::index_type source = g.numNodes();
    gl::index_type dest = g.numNodes();

    for (auto it = g.node_cbegin(); it != g.node_cend(); it++)
    {
        if (it->label() == " 5000") // change this
        {
            source = it->id();
            break;
        }
    }
    for (auto it = g.node_cbegin(); it != g.node_cend(); it++)
    {
        if (it->label() == " 7000") // change this
        {
            dest = it->id();
            break;
        }
    }
    if(source == g.numNodes()) {
        std::cout << "Source location not found." << std::endl;
        return 1;
    }
    if(dest == g.numNodes()) {
        std::cout << "Destination location not found." << std::endl;
        return 1;
    }

    gl::algorithm::dijkstraMdu dijkstra;
    dijkstra.compute(g,source);
    auto path = dijkstra.getPath(dest);

    for (gl::index_type i = 0; i < path.size() - 2; i++)
    {
        g.updateEdge(path[i], path[i + 1], gl::Color("blue"));
        if (i > 0)
        {
            g.updateNode(path[i], gl::Color("blue"));
        }
    }

    g.updateNode(source, gl::Color("green"));
    g.updateNode(dest, gl::Color("red"));

    std::ofstream out("build/test/switzerland.tex");
    gl::external::writeTikzToStream2(out, g, false, false);
    out.close();

    std::cout << "LATEX FILE GENERATED." << std::endl << "ATTENTION: Compiling latex might take up to 5 minutes." << std::endl;
    gl::io::compileLatex("build/test/switzerland.tex","--output-directory=build/test");
    return 0;
}
