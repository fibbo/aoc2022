#include <boost/algorithm/string.hpp>

#include "open_file.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

void part1(const std::vector<std::string> &lines) {
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

int main(int /*argc*/, char **argv) {

  const auto lines = split(read_file(open_file(argv[1])), "\n");
  part1(lines);

  return 0;
}
