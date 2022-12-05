#include "aoc_lib.hpp"
#include "range/v3/iterator/operations.hpp"
#include "range/v3/view/filter.hpp"
#include "range/v3/view/transform.hpp"
#include <cstdint>
#include <iostream>

using namespace pgl::aoc;

class Section {
public:
  explicit Section(const std::string &sectionString) {
    const auto tokens = split_line(sectionString, "-");
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

template <typename Filter>
auto countDoubleWork(const Tokens &tokens, Filter &&f) {
  const auto overlapCount = ranges::distance(
      tokens | ranges::views::transform([](const std::string &line) {
        const auto tokens = split_line(line, ",");
        return std::make_pair(Section(tokens[0]), Section(tokens[1]));
      }) |
      ranges::views::filter([f = std::move(f)](const auto &pair) {
        return f(pair.first, pair.second);
      }));
  return overlapCount;
}

int main(int /*argc*/, char **argv) {
  const auto lines = read_lines(argv[1]);

  const auto fullyContainedCount =
      countDoubleWork(lines, [](const Section &section, const Section &other) {
        return contains(section, other);
        ;
      });
  const auto overlapCount =
      countDoubleWork(lines, [](const Section &section, const Section &other) {
        return section.overlaps(other);
      });

  std::cout << "Number of fully contained sections: " << fullyContainedCount
            << std::endl;
  std::cout << "Number of overlaps: " << overlapCount << std::endl;
  return 0;
}
