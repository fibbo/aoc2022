#include "open_file.hpp"
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

std::vector<std::string> split(const std::stringstream &stringstream,
                               const std::string &delim) {
  std::vector<std::string> lines;
  boost::algorithm::split(lines, stringstream.str(), boost::is_any_of(delim));
  return lines;
}

} // namespace pgl::aoc
