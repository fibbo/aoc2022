#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace pgl::aoc
{

// Maps a-z and A-Z to 1-52
constexpr uint32_t convertCharToInt(char c)
{
  // a-z have priority 1-26
  // A-Z have priority 27-52
  return c >= 'a' ? c - 'a' + 1 : c - 'A' + 27;
}

static_assert(convertCharToInt('a') == 1);
static_assert(convertCharToInt('z') == 26);
static_assert(convertCharToInt('A') == 27);
static_assert(convertCharToInt('Z') == 52);


std::fstream open_file(const std::string& filePath);

std::stringstream read_file(const std::fstream& file);

using Lines = std::vector<std::string>;
using Tokens = std::vector<std::string>;

Tokens split_stringstream(
    const std::stringstream& stringstream, const std::string& delim = "\n");

Lines read_lines(const std::string& filePath, const std::string& delim = "\n");

Tokens split_line(const std::string& line, const std::string& delim);

struct Point
{
  Point();
  Point(int64_t x, int64_t y);

  int64_t x;
  int64_t y;
  bool operator==(const Point& p) const;
};

}  // namespace pgl::aoc

namespace std
{
template <>
struct hash<pgl::aoc::Point>
{
  size_t operator()(const pgl::aoc::Point& p) const;
};

}  // namespace std
