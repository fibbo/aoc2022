#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

using namespace pgl::aoc;

void part1(const Lines &lines) {
  uint32_t calCount{0};
  uint32_t bigGuyCal{0};

  for (const auto &line : lines) {
    if (!line.empty()) {
      calCount += std::stoull(line);
    } else {
      if (calCount > bigGuyCal) {
        bigGuyCal = calCount;
      }
      calCount = 0;
    }
  }
  std::cout << bigGuyCal << std::endl;
}

void part2(const Lines &lines) {
  std::vector<uint32_t> calCounts;
  uint32_t calCount{0};
  for (const auto &line : lines) {
    if (!line.empty()) {
      calCount += std::stoull(line);
    } else {
      calCounts.push_back(calCount);
      calCount = 0;
    }
  }

  std::sort(calCounts.begin(), calCounts.end(),
            [](const auto &a, const auto &b) { return a > b; });
  const auto calories =
      std::accumulate(calCounts.begin(), std::next(calCounts.begin(), 3), 0,
                      [](const auto &a, const auto &b) { return a + b; });

  std::cout << calories << std::endl;
}

int main(int /*argc*/, char **argv) {

  const auto lines = read_lines(argv[1]);
  part1(lines);
  part2(lines);

  return 0;
}
