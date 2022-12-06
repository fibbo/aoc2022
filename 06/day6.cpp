#include "aoc_lib.hpp"
#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <unordered_set>

using namespace pgl::aoc;

uint32_t findSequenceStart(const std::string &sequence,
                           uint32_t uniqueCharacters) {
  size_t positionMarker{0};
  std::vector<char> buffer;

  for (; positionMarker < sequence.size(); ++positionMarker) {
    buffer.push_back(sequence[positionMarker]);
    if (buffer.size() < uniqueCharacters) {
      continue;
    }

    auto checkForUnique = buffer;
    std::sort(checkForUnique.begin(), checkForUnique.end());
    auto last = std::unique(checkForUnique.begin(), checkForUnique.end());
    checkForUnique.erase(last, checkForUnique.end());
    if (checkForUnique.size() == uniqueCharacters) {
      break;
    }
    buffer.erase(buffer.begin());
  }
  return ++positionMarker;
}

int main(int argc, char **argv) {
  Lines lines;
  if (argc == 2) {
    lines = read_lines(argv[1]);
  } else {
    lines = read_lines("06/input_example.txt");
  }

  for (const auto &line : lines) {
    std::cout << findSequenceStart(line, 4) << std::endl;
    std::cout << findSequenceStart(line, 14) << std::endl;
  }

  return 0;
}
