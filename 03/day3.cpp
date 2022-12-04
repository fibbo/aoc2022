#include "aoc_lib.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string_view>
#include <unordered_set>

using namespace pgl::aoc;

constexpr uint32_t prioMap(char c) {
  // a-z have priority 1-26
  // A-Z have priority 27-52
  return c >= 'a' ? c - 'a' + 1 : c - 'A' + 27;
}

static_assert(prioMap('a') == 1);
static_assert(prioMap('z') == 26);
static_assert(prioMap('A') == 27);
static_assert(prioMap('Z') == 52);

void part1(const Lines &backpacks) {
  std::unordered_set<char> seen;
  uint32_t prioSum{0};
  for (const auto &line : backpacks) {
    {
      const auto firstCompartment =
          std::string_view(line.c_str(), line.size() / 2);
      std::for_each(firstCompartment.begin(), firstCompartment.end(),
                    [&seen](const auto &c) { seen.insert(c); });
    }
    {
      const auto secondCompartment =
          std::string_view(line.c_str() + line.size() / 2);
      std::any_of(secondCompartment.begin(), secondCompartment.end(),
                  [&seen, &prioSum](const auto &c) {
                    if (!seen.contains(c)) {
                      return false;
                    }
                    prioSum += prioMap(c);
                    return true;
                  });
    }
    seen.clear();
  }
  std::cout << prioSum << std::endl;
}

void part2(const Lines &backpacks) {
  uint32_t prioSum{0};
  for (size_t i = 0; i < backpacks.size(); i += 3) {
    const auto group = std::to_array<std::set<char>>(
        {{backpacks[i].begin(), backpacks[i].end()},
         {backpacks[i + 1].begin(), backpacks[i + 1].end()},
         {backpacks[i + 2].begin(), backpacks[i + 2].end()}});

    std::vector<char> intersect1_2;
    std::set_intersection(group[0].begin(), group[0].end(), group[1].begin(),
                          group[1].end(), std::back_inserter(intersect1_2));

    std::vector<char> intersection;
    std::set_intersection(intersect1_2.begin(), intersect1_2.end(),
                          group[2].begin(), group[2].end(),
                          std::back_inserter(intersection));

    assert(intersection.size() == 1);
    prioSum += prioMap(intersection[0]);
  }
  std::cout << prioSum << std::endl;
}

int main(int /*argc*/, char **argv) {
  auto lines = read_lines(argv[1]);
  part1(lines);
  part2(lines);

  return 0;
}
