#include "aoc_lib.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace pgl::aoc {

std::fstream open_file(const std::string& filePath) {
  std::fstream file{filePath};
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  return file;
}

std::stringstream read_file(const std::fstream& file) {
  std::stringstream ss;
  ss << file.rdbuf();
  return ss;
}

Tokens split_stringstream(
    const std::stringstream& stringstream, const std::string& delim) {
  std::vector<std::string> lines;
  boost::algorithm::split(lines, stringstream.str(), boost::is_any_of(delim));
  while (lines.back().empty()) {
    lines.pop_back();
  }
  return lines;
}

Lines read_lines(const std::string& filePath, const std::string& delim) {
  return split_stringstream(read_file(open_file(filePath)), delim);
}

// Not really necessary function, but I'm too lazy to type this out every time
// i.e. boost::is_any_of(",") is too long to type :)
Tokens split_line(const std::string& line, const std::string& delim) {
  Tokens tokens;
  boost::algorithm::split(tokens, line, boost::is_any_of(delim));
  return tokens;
}

Point::Point()
    : x{0}
    , y{0} {
}

Point::Point(int64_t x, int64_t y)
    : x(x)
    , y(y) {
}

bool Point::operator==(const Point& p) const {
  return p.x == x && p.y == y;
}


}  // namespace pgl::aoc

namespace std {
size_t hash<pgl::aoc::Point>::operator()(const pgl::aoc::Point& p) const {
  return (53 + p.x) * 53 + p.y;
}
}  // namespace std
