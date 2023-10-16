#include "aoc_lib.hpp"
#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <unordered_set>

using namespace pgl::aoc;

uint32_t findSequenceStart(
    const std::string& sequence, uint32_t uniqueCharacters)
{
  std::deque<char> buffer;

  size_t positionMarker{0};
  for (; positionMarker < sequence.size(); ++positionMarker)
  {
    buffer.push_back(sequence[positionMarker]);
    if (buffer.size() < uniqueCharacters)
    {
      continue;
    }

    std::unordered_set<char> characterSet{buffer.begin(), buffer.end()};
    if (characterSet.size() == uniqueCharacters)
    {
      break;
    }
    buffer.pop_front();
  }
  return ++positionMarker;
}

int main(int argc, char** argv)
{
  Lines lines;
  if (argc == 2)
  {
    lines = read_lines(argv[1]);
  }
  else
  {
    lines = read_lines("06/input_example.txt");
  }

  for (const auto& line : lines)
  {
    std::cout << findSequenceStart(line, 4) << std::endl;
    std::cout << findSequenceStart(line, 14) << std::endl;
  }

  return 0;
}
