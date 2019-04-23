#include <graphlib/gl>
#include <graphlib/external>

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("test/graph.yml");

    reader.read();

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    auto add_edge = [](auto g_ptr) { 
        g_ptr->setEdge(0, 1, 1.4);
        g_ptr->setEdge(1, 2, 3.3); };
    auto print_graph = [](auto g_ptr) { std::cout << *g_ptr; };

    //std::visit(add_edge, g);
    std::visit(print_graph, g);

    std::ofstream out("build/test/OUTPUT.tex");
    std::visit([&out](auto arg) { gl::external::writeTikzToStream2(out, *arg); }, g);
    out.close();

    return 0;
}
