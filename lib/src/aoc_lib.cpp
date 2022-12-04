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

Tokens split_stringstream(const std::stringstream &stringstream,
                          const std::string &delim) {
  std::vector<std::string> lines;
  boost::algorithm::split(lines, stringstream.str(), boost::is_any_of(delim));
  while (lines.back().empty()) {
    lines.pop_back();
  }
  return lines;
}

Lines read_lines(const std::string &filePath) {
  return split_stringstream(read_file(open_file(filePath)), "\n");
}

// Not really necessary function, but I'm too lazy to type this out every time
// i.e. boost::is_any_of(",") is too long to type :)
Tokens split_line(const std::string &line, const std::string &delim) {
  Tokens tokens;
  boost::algorithm::split(tokens, line, boost::is_any_of(delim));
  return tokens;
}

} // namespace pgl::aoc
