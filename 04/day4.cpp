#include "aoc_lib.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cstdint>
#include <iostream>

using namespace pgl::aoc;

class Section {
public:
  explicit Section(const std::string &sectionString) {
    std::vector<std::string> tokens;
    boost::split(tokens, sectionString, boost::is_any_of("-"));
    if (tokens.size() != 2) {
      throw std::runtime_error("Invalid section string: " + sectionString);
    }
    begin_ = std::stoi(tokens[0]);
    end_ = std::stoi(tokens[1]);
  }

  // Check if one section contains another
  bool contains(const Section &other) const {
    return begin_ <= other.begin_ && other.end_ <= end_;
  }

  // Check if two sections overlap
  bool overlaps(const Section &other) const {
    return (begin_ <= other.begin_ && other.begin_ <= end_) ||
           (other.begin_ <= begin_ && begin_ <= other.end_);
  }

private:
  uint32_t begin_;
  uint32_t end_;
};

// Check if one section contains another
bool contains(const Section &section, const Section &other) {
  return section.contains(other) || other.contains(section);
}

int main(int /*argc*/, char **argv) {
  const auto lines = read_lines(argv[1]);
  std::vector<Section> sections;

  uint32_t nFullyContains{0};
  uint32_t nOverlaps{0};

  for (const auto &line : lines) {
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(","));
    if (tokens.size() != 2) {
      throw std::runtime_error("Invalid line: " + line);
    }
    Section a(tokens[0]);
    Section b(tokens[1]);

    if (contains(a, b)) {
      nFullyContains++;
    }

    if (a.overlaps(b)) {
      nOverlaps++;
    }
  }
  std::cout << "Number of fully contained sections: " << nFullyContains
            << std::endl;
  std::cout << "Number of overlaps: " << nOverlaps << std::endl;
  return 0;
}
