#include <iostream>
#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("examples/input/switzerland.yml");  // assumes running from project root folder

    auto g = *std::get<gl::graphLdu *>(reader.get());

    gl::index_type source = g.numNodes();
    gl::index_type dest = g.numNodes();

    /**
     * Pass in two command line arguments to change the Dijkstra targets.
     * Accepted are (probably) any two Swiss Post Codes.
     * Example (Path from Basel to Zurich): ./SwitzerlandDijkstra 4000 8000
     */
    std::string source_label (argc == 3 ? " " + std::string(argv[1]) : " 5000");
    std::string target_label (argc == 3 ? " " + std::string(argv[2]) : " 7000");

    for (auto it = g.node_cbegin(); it != g.node_cend(); it++)
    {
        if (it->label() == source_label)
        {
            source = it->id();
            break;
        }
    }
    for (auto it = g.node_cbegin(); it != g.node_cend(); it++)
    {
        if (it->label() == target_label)
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

    gl::algorithm::dijkstraLdu dijkstra(g,source);
    auto path = dijkstra.getPath(dest);

    for (gl::index_type i = 0; i < path.size() - 2; i++)
    {
        g.updateEdge(path[i], path[i + 1], gl::Color("blue"));
        if (i > 0)
        {
            g.updateNode(path[i], gl::Color("blue"));
        }
    }

    g.updateNode(source, gl::Color("lime"));
    g.updateNode(dest, gl::Color("red"));

    std::ofstream out("build/examples/switzerland.tex");
    gl::external::writeTikzNetwork(out, g, false, false);
    out.close();

    std::cout << "LATEX FILE GENERATED: build/examples/switzerland.tex" << std::endl << "ATTENTION: Compiling latex might take up to 5 minutes." << std::endl;
    // gl::io::compileLatex("switzerland.tex");
    return 0;
}
