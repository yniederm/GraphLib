#ifndef GL_COMPILE_LATEX_HPP
#define GL_COMPILE_LATEX_HPP

#include <string>

namespace gl {
namespace io {

/**
 * @brief Invokes lualatex command to compile tex to pdf
 * @param filename Name of the file to compile
 * @param arguments Optional additional arguments
 */
void compileLatex(const char *filename, const char *arguments = "")
{
    std::cout << "Compiling latex..." << std::endl
              << "If this fails because of permissions within the \"convert\" command, do the following:" << std::endl
              << "In the files /etc/ImageMagick-6/policy.xml && /etc/ImageMagick-7/policy.xml" << std::endl
              << "change the line containing" << std::endl
              << "<policy domain=\"coder\" rights=\"none\" pattern=\"PDF\" />" << std::endl
              << "to" << std::endl
              << "<policy domain=\"coder\" rights=\"read\" pattern=\"PDF\" />" << std::endl;

    std::string command = "lualatex --interaction=nonstopmode ";

    command += std::string(arguments);
    command += " " + std::string(filename);

    std::string file = std::string(filename);
    std::size_t pos = file.find_last_of(".");

    std::string filename_without_extension = file.substr(0, pos);

    std::string command2 = "convert -density 500 " +
                           filename_without_extension + ".pdf -quality 100 " + filename_without_extension + ".png";

    // supress latex output, but save as log
    command += " > " + filename_without_extension + "_latex_output.txt";
    system(command.data());  // pdflatex
    system(command2.data()); // convert to png

    std::cout << "Generated " << filename_without_extension << ".png" << std::endl;
}

} // namespace io
} // namespace gl

#endif // GL_COMPILE_LATEX_HPP