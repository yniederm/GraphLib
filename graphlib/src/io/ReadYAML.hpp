#ifndef READ_YAML_HPP
#define READ_YAML_HPP

#include "../structures/Graph.hpp"
#include <fstream>
#include <iostream> // for debugging
#include <variant>
#include <sstream>

namespace gl
{
namespace io
{
// define those macros for usage with printing
/* usage: get the IO_Graph_variant using YAMLReader::get
 * then, write your normal code lines using IO_CALL_ON_GRAPH and the arugment IO_GRAPH
 * e.g. for pringing (and graph_variant_type g = reader.get();)
 * IO_CALL_ON_GRAPH(g, std::cout << IO_GRAPH << std::endl;);
 * 
 * If it must be called directly, use (IO_GRAPH).FUNCTION, e.g
 * (IO_GRAPH).setEdge(0, 1);
 */
#define IO_GRAPH *arg
#define IO_CALL_ON_GRAPH(g, func) std::visit([&](auto arg) { func; }, g)

class YAMLReader
{
public:
    using graph_variant_type = std::variant<graphMdu *, graphMdd *, graphLdu *, graphLdd *,
                                            graphMfu *, graphMfd *, graphLfu *, graphLfd *,
                                            graphMiu *, graphMid *, graphLiu *, graphLid *>;

    graph_variant_type graph;

    graph_variant_type get() { return graph; }

    YAMLReader()
    {
    }
    YAMLReader(const char *filename)
    {
        std::cout << "Reading " << filename << std::endl;
        stream_ = std::fstream(filename);
        graph = graph_variant_type();
        GL_ASSERT(stream_.is_open(), "File could not be opened");
    }

    void read()
    {
        std::string value_type, storage_type, direction_type, graph_label;
        int number_of_nodes;

        // {{from,to},{weight, color}}
        using edge_t = std::pair<std::pair<unsigned int, unsigned int>, std::pair<double, gl::Color>>;
        using idx_t = graphMdd::idx_t;

        std::vector<edge_t> edges;
        std::string line;
        while (getline(stream_, line))
        {
            // comments on lines
            if (line[0] == '#' || line.empty())
                continue;
            std::size_t delimiterPos = line.find(": "); // including space
            std::string name = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 2);
            if (name == "value_type")
            {
                value_type = value;
            }
            else if (name == "direction_type")
            {
                direction_type = value;
            }
            else if (name == "storage_type")
            {
                storage_type = value;
            }
            else if (name == "number_nodes")
            {
                number_of_nodes = std::stoi(value);
            }
            else if (name == "name")
            {
                graph_label = value;
            }
            else if (name == "edge")
            {
                std::stringstream ss(value);
                idx_t a, b;
                double weight = 1;
                ss >> a >> b;
                // if ss not empty, read weight
                if (!ss.eof())
                {
                    ss >> weight;
                }
                gl::Color c(0, 0, 0);
                unsigned int hex;
                if (!ss.eof())
                {
                    ss >> std::hex >> hex;
                    c.hex(hex);
                }
                edges.push_back({{a, b}, {weight, c}});
            }
            else
            {
                std::cout << "Unrecognized option" << std::endl;
            }
        }

        if (value_type == "double" && storage_type == "Matrix" && direction_type == "Undirected")
        {
            graph = new graphMdu(number_of_nodes, graph_label);
        }
        else if (value_type == "double" && storage_type == "Matrix" && direction_type == "Directed")
        {
            graph = new graphMdd(number_of_nodes, graph_label);
        }
        else if (value_type == "double" && storage_type == "List" && direction_type == "Undirected")
        {
            graph = new graphLdu(number_of_nodes, graph_label);
        }
        else if (value_type == "double" && storage_type == "List" && direction_type == "Directed")
        {
            graph = new graphLdd(number_of_nodes, graph_label);
        }
        else if (value_type == "float" && storage_type == "Matrix" && direction_type == "Undirected")
        {
            graph = new graphMfu(number_of_nodes, graph_label);
        }
        else if (value_type == "float" && storage_type == "Matrix" && direction_type == "Directed")
        {
            graph = new graphMfd(number_of_nodes, graph_label);
        }
        else if (value_type == "float" && storage_type == "List" && direction_type == "Undirected")
        {
            graph = new graphLfu(number_of_nodes, graph_label);
        }
        else if (value_type == "float" && storage_type == "List" && direction_type == "Directed")
        {
            graph = new graphLfd(number_of_nodes, graph_label);
        }
        else if (value_type == "int" && storage_type == "Matrix" && direction_type == "Undirected")
        {
            graph = new graphMiu(number_of_nodes, graph_label);
        }
        else if (value_type == "int" && storage_type == "Matrix" && direction_type == "Directed")
        {
            graph = new graphMid(number_of_nodes, graph_label);
        }
        else if (value_type == "int" && storage_type == "List" && direction_type == "Undirected")
        {
            graph = new graphLiu(number_of_nodes, graph_label);
        }
        else if (value_type == "int" && storage_type == "List" && direction_type == "Directed")
        {
            graph = new graphLid(number_of_nodes, graph_label);
        }
        else
        {
            GL_ASSERT(false, "Please enter valid data into config.");
        }

        // add all edges to the graph
        for (edge_t &e : edges)
        {
            IO_CALL_ON_GRAPH(graph, (IO_GRAPH).setEdge(e.first.first, e.first.second, e.second.first, e.second.second));
        }
    }

private:
    std::fstream stream_;
};

} // namespace io
} // namespace gl

#endif