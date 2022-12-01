#include "open_file.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

using namespace pgl::aoc;

void part1(const Lines &lines) {
  uint32_t calCount = 0;
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

  std::cout << calCounts[0] + calCounts[1] + calCounts[2] << std::endl;
}

int main(int /*argc*/, char **argv) {

  const auto lines = split(read_file(open_file(argv[1])), "\n");
  part1(lines);
  part2(lines);

  return 0;
}
