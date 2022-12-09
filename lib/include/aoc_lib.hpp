#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace pgl::aoc {

std::fstream open_file(const std::string& filePath);

std::stringstream read_file(const std::fstream& file);

using Lines = std::vector<std::string>;
using Tokens = std::vector<std::string>;

Tokens split_stringstream(
    const std::stringstream& stringstream, const std::string& delim = "\n");

Lines read_lines(const std::string& filePath);

Tokens split_line(const std::string& line, const std::string& delim);

struct Point {
  Point();
  Point(int64_t x, int64_t y);

  int64_t x;
  int64_t y;
  bool operator==(const Point& p) const;
};
}  // namespace pgl::aoc

namespace std {
template <>
struct hash<pgl::aoc::Point> {
  size_t operator()(const pgl::aoc::Point& p) const;
};
}  // namespace std
