#include <graphlib/gl>

int main(int argc, char const *argv[])
{
    const int idx = 0;
    gl::io::YAMLReader reader("../test/graph.yml");

    reader.read();

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    auto add_edge = [](auto g_ptr) { g_ptr->setEdge(0, 1); };
    auto print_graph = [](auto g_ptr) { std::cout << *g_ptr; };

    std::visit(add_edge, g);
    std::visit(print_graph, g);

    return 0;
}
