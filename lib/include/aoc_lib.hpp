#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace pgl::aoc {

std::fstream open_file(const std::string &filePath);

std::stringstream read_file(const std::fstream &file);

using Lines = std::vector<std::string>;
using Tokens = std::vector<std::string>;

Tokens split(const std::stringstream &stringstream,
             const std::string &delim = "\n");

Lines read_lines(const std::string &filePath);

} // namespace pgl::aoc
