#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("test/graph.yml");

    reader.read();

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    // auto print_graph = [](auto g_ptr) { std::cout << *g_ptr; };
    // std::visit(print_graph, g);
    IO_CALL_ON_GRAPH(g, std::cout << IO_GRAPH << std::endl);

    std::ofstream out("build/test/OUTPUT.tex");

    //std::visit([&out](auto arg) { gl::external::writeTikzToStream2(out, *arg); }, g);
    IO_CALL_ON_GRAPH(g, gl::external::writeTikzToStream2(out, IO_GRAPH));

    out.close();

    return 0;
}
