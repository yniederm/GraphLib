#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <string>

namespace gl
{

namespace io
{

/**
 * @brief Invokes pdflatex command to compile tex to pdf
 * @param filename Name of the file to compile
 * @param arguments Optional additional arguments
 */
void compileLatex(const char *filename, const char *arguments = "")
{
    std::string command = "pdflatex --interaction=nonstopmode ";
    command += std::string(arguments);
    command += " " + std::string(filename);
    system(command.data());
}

} /* namespace io */

} /* namespace gl */

#endif /* GENERAL_HPP */