#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace pgl::aoc;

class Signal {};
int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "13/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);

  for (const auto& line : lines) {
    std::cout << line << std::endl;
  }

  return 0;
}
