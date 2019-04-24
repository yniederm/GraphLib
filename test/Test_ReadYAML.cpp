#include <graphlib/gl>
#include <graphlib/external> // for writeTIKZ

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("test/graph.yml");

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    // std::visit([](auto g_ptr) { std::cout << *g_ptr; }, g);
    //IO_CALL_ON_GRAPH(g, std::cout << IO_GRAPH << std::endl);

    std::ofstream out("build/test/OUTPUT.tex");

    //std::visit([&out](auto arg) { gl::external::writeTikzToStream2(out, *arg); }, g);
    IO_CALL_ON_GRAPH(g, gl::external::writeTikzToStream2(out, IO_GRAPH));
    out.close();

    return 0;
}
