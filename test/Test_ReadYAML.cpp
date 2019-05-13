#include <graphlib/gl>
#include <graphlib/external> // for writeTIKZ

int main(int argc, char const *argv[])
{
    gl::io::YAMLReader reader("../../test/input/graph.yml"); // assumes running from build/test folder

    gl::io::YAMLReader::graph_variant_type g = reader.get();

    std::ofstream out("ReadYAML.tex");

    IO_CALL_ON_GRAPH(g, gl::external::writeTikzToStream2(out, IO_GRAPH));
    out.close();

    // gl::io::compileLatex("ReadYAML.tex");

    return 0;
}
