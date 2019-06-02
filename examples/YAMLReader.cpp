#include <graphlib/gl>
#include <graphlib/external> // for writeTIKZ

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("../../examples/input/graph.yml"); // assumes running from build/test folder

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    std::ofstream out("YAMLReader.tex");

    IO_CALL_ON_GRAPH(g, gl::external::writeTikzNetwork(out, IO_GRAPH));
    out.close();

    // gl::io::compileLatex("YAMLReader.tex");

    return 0;
}
