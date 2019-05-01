#include <graphlib/gl>
#include <graphlib/external> // for writeTIKZ

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("test/graph.yml");

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    std::ofstream out("build/test/OUTPUT.tex");

    IO_CALL_ON_GRAPH(g, gl::external::writeTikzToStream2(out, IO_GRAPH, true));
    out.close();

    gl::io::compileLatex("build/test/OUTPUT.tex", "--output-directory=build/test/");

    return 0;
}
