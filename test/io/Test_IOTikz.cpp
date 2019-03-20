#include "../../src/structures/ListGraph.hpp"
#include "../../src/structures/MatrixGraph.hpp"

template <class SCALAR>
void print_tikz(gl::Graph<SCALAR> &g)
{
    std::cout << "\\documentclass[border=10pt]{standalone}\n"
              << "\\usepackage{tkz-graph}\n"
              << "\\GraphInit[vstyle = Shade]\n"
              << "\\tikzset{\n"
              << "  LabelStyle/.style = { rectangle, rounded corners, draw, minimum width = 2em,\n"
              << "      fill = yellow!50, text = red, font = \\bfseries },\n"
              << "  VertexStyle/.append style = { inner sep=5pt,\n"
              << "      font = \\Large\\bfseries},\n"
              << "  EdgeStyle/.append style = {->, bend left} }\n"
              << "\\thispagestyle{empty}\n"
              << "\\begin{document}\n"
              << "\\begin{tikzpicture}\n"
              << "\\SetGraphUnit{5}\n";
    for (int i = 0; i < g.numNodes(); i++)
    {
        if (i == 0)
            std::cout << "\\Vertex{" << i << "}" << std::endl;
        else
            std::cout << "\\WE(" << i - 1 << "){" << i << "}" << std::endl;
    }

    int count = 0;
    for (int i = 0; i < g.numNodes(); i++)
    {
        for (int j = 0; j < g.numNodes(); j++)
        {
            if (g.hasEdge(i, j))
            {
                if (i == j)
                {
                    std::cout << "\\Loop[dist=4cm,dir=NO,label=" << count << "](" << i << ".west)\n";
                }
                else
                {
                    std::cout << "\\Edge[label=" << count << "](" << i << ")(" << j << ")\n";
                }
                count++;
            }
        }
    }

    std::cout << "\\end{tikzpicture}\n\\end{document}" << std::endl;
}

int main(int argc, char const *argv[])
{
    using mgraph = gl::MGraph<double>;

    mgraph g(3);
    g.setEdge(0, 1, 1);
    g.setEdge(1, 2, 2);
    g.setEdge(2, 1, 3);
    g.setEdge(1, 0, 4);
    g.setEdge(0, 0, 5);
    g.setEdge(2, 2, 6);
    g.setEdge(0, 2, 7);
    g.setEdge(2, 0, 8);

    print_tikz(g);

    return 0;
}
