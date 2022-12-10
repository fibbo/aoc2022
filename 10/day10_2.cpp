#include "aoc_lib.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace pgl::aoc;

void checkSignal(
    uint32_t cycleCount, int64_t register_, uint32_t& signalStrength) {
  if ((cycleCount + 20) % 40 == 0) {
    signalStrength += register_ * cycleCount;
    std::cout << "Signal strength: " << signalStrength << std::endl;
  }
}

void drawPixel(
    std::vector<char>& screen, uint32_t cycleCount, int64_t register_) {
  const auto currentPixel = (cycleCount - 1) % 40;
  if (currentPixel >= register_ - 1 && currentPixel <= register_ + 1) {
    screen.push_back('#');
  } else {
    screen.push_back('.');
  }
}

int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "10/input_example.txt";
  }

  const auto lines = read_lines(fileName);
  int64_t register_{1};
  uint32_t cycleCount{0};
  uint32_t signalStrength{0};
  std::vector<char> screen;
  for (const auto& line : lines) {
    ++cycleCount;
    checkSignal(cycleCount, register_, signalStrength);
    drawPixel(screen, cycleCount, register_);

    if (line.starts_with("addx")) {
      ++cycleCount;
      checkSignal(cycleCount, register_, signalStrength);
      drawPixel(screen, cycleCount, register_);
      const auto x = std::stoll(line.substr(5));
      register_ += x;
    }
  }

  for (auto i = 0U; i < 240; ++i) {
    if (i % 40 == 0) {
      std::cout << std::endl;
    }
    std::cout << screen[i];
  }
  std::cout << std::endl;

  return 0;
}
