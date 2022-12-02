#include "aoc_lib.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace pgl::aoc {

std::fstream open_file(const std::string &filePath) {
  std::fstream file{filePath};
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  return file;
}

std::stringstream read_file(const std::fstream &file) {
  std::stringstream ss;
  ss << file.rdbuf();
  return ss;
}

Lines split(const std::stringstream &stringstream, const std::string &delim) {
  std::vector<std::string> lines;
  boost::algorithm::split(lines, stringstream.str(), boost::is_any_of(delim));
  return lines;
}

Lines read_lines(const std::string &filePath, const std::string &delim) {
  return split(read_file(open_file(filePath)), delim);
}

} // namespace pgl::aoc
