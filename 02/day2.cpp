#include "aoc_lib.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <unordered_map>

using namespace pgl::aoc;

static constexpr int rockValue = 1;
static constexpr int paperValue = 2;
static constexpr int scissorsValue = 3;

static constexpr int loss = 0;
static constexpr int draw = 3;
static constexpr int win = 6;

// A Rock
// B Paper
// C Scissors
static const std::unordered_map<std::string, uint32_t> outcomeScopeMapPart1 = {
    {"A X", 4},  // Draw with Rock
    {"A Y", 8},  // Win with Paper
    {"A Z", 3},  // Loss with Scissors
    {"B X", 1},  // Loss with Rock
    {"B Y", 5},  // Draw with Paper
    {"B Z", 9},  // Win with Scissors
    {"C X", 7},  // Win with Rock
    {"C Y", 2},  // Loss with Paper
    {"C Z", 6},  // Draw with Scissors
};

static const std::unordered_map<std::string, uint32_t> outcomeScopeMapPart2 = {
    {"A X", loss + scissorsValue},  // Lose against Rock (play Scissors)
    {"A Y", draw + rockValue},      // Draw against Rock (play Rock)
    {"A Z", win + paperValue},      // Win against Rock (play Paper)
    {"B X", loss + rockValue},      // Lose against Paper (play Rock)
    {"B Y", draw + paperValue},     // Draw against Paper (play Paper)
    {"B Z", win + scissorsValue},   // Win against Paper (play Scissors)
    {"C X", loss + paperValue},     // Lose against Scissors (play Paper)
    {"C Y", draw + scissorsValue},  // Draw against Scissors (play Scissors)
    {"C Z", win + rockValue},       // Win against Scissors (play Rock)
};

void solve(
    const Lines& lines,
    const std::unordered_map<std::string, uint32_t>& outcomeScopeMap)
{
  uint32_t total{0};
  for (const auto& line : lines)
  {
    if (line.empty())
    {
      continue;
    }
    const auto it = outcomeScopeMap.find(line);
    if (it != outcomeScopeMap.end())
    {
      total += it->second;
    }
    else
    {
      std::cerr << "Unknown outcome: " << line << std::endl;
    }
  }
  std::cout << total << std::endl;
}

int main(int /*argc*/, char** argv)
{
  Lines lines = read_lines(argv[1]);
  solve(lines, outcomeScopeMapPart1);
  solve(lines, outcomeScopeMapPart2);
  return 0;
}
