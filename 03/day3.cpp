/*
 * AoC 2022 Day 3
 * https://adventofcode.com/2022/day/3
 */

#include "aoc_lib.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <string_view>
#include <unordered_set>

using namespace pgl::aoc;

void part1(const Lines& backpacks)
{
  std::unordered_set<char> seen;
  uint32_t prioSum{0};
  for (const auto& line : backpacks)
  {
    {
      const auto firstCompartment =
          std::string_view(line.c_str(), line.size() / 2);

      std::for_each(
          firstCompartment.begin(),
          firstCompartment.end(),
          [&seen](const auto& c) { seen.insert(c); });
    }
    {
      const auto secondCompartment =
          std::string_view(line.c_str() + line.size() / 2);


      // NOTE: This assumes that only ever one element is in both compartments
      // which is OK according to the problem description.
      std::ignore = std::any_of(
          secondCompartment.begin(),
          secondCompartment.end(),
          [&seen, &prioSum](const auto& c) -> auto
          {
            if (!seen.contains(c))
            {
              return false;
            }
            prioSum += convertCharToInt(c);
            return true;
          });
    }
    seen.clear();
  }
  std::cout << prioSum << std::endl;
}

void part2(const Lines& backpacks)
{
  uint32_t prioSum{0};
  for (size_t i = 0; i < backpacks.size(); i += 3)
  {
    const auto group = std::to_array<std::set<char>>(
        {{backpacks[i].begin(), backpacks[i].end()},
         {backpacks[i + 1].begin(), backpacks[i + 1].end()},
         {backpacks[i + 2].begin(), backpacks[i + 2].end()}});

    std::vector<char> intersect1_2;
    std::set_intersection(
        group[0].begin(),
        group[0].end(),
        group[1].begin(),
        group[1].end(),
        std::back_inserter(intersect1_2));

    std::vector<char> intersection;
    std::set_intersection(
        intersect1_2.begin(),
        intersect1_2.end(),
        group[2].begin(),
        group[2].end(),
        std::back_inserter(intersection));

    assert(intersection.size() == 1);
    prioSum += convertCharToInt(intersection[0]);
  }
  std::cout << prioSum << std::endl;
}

int main(int /*argc*/, char** argv)
{
  auto lines = read_lines(argv[1]);
  part1(lines);
  part2(lines);

  return 0;
}
