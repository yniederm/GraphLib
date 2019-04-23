#ifndef READ_YAML_HPP
#define READ_YAML_HPP

#include "../structures/Graph.hpp"
#include <fstream>
#include <iostream> // for debugging
#include <variant>

namespace gl
{
namespace io
{

class YAMLReader
{
public:
    using graph_variant_type = std::variant<graphMdu *, graphMdd *, graphLdu *, graphLdd *>;

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
        std::string value_type, storage_type, direction_type, graph_name;
        int number_of_nodes;

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
                graph_name = name;
            }
            else
            {
                std::cout << "Unrecognized option" << std::endl;
            }
        }

        if (value_type == "double" && storage_type == "Matrix" && direction_type == "Undirected")
        {
            graph = new graphMdu(number_of_nodes, graph_name);
        }
        if (value_type == "double" && storage_type == "Matrix" && direction_type == "Directed")
        {
            graph = new graphMdd(number_of_nodes, graph_name);
        }
        if (value_type == "double" && storage_type == "List" && direction_type == "Undirected")
        {
            graph = new graphLdu(number_of_nodes, graph_name);
        }
        if (value_type == "double" && storage_type == "List" && direction_type == "Directed")
        {
            graph = new graphLdd(number_of_nodes, graph_name);
        }
    }

private:
    std::fstream stream_;
};

} // namespace io
} // namespace gl

#endif