#include "aoc_lib.hpp"
#include <algorithm>
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

std::set<char> toSet(std::string_view sv) {
  std::set<char> set;
  std::for_each(sv.begin(), sv.end(), [&set](const auto c) { set.insert(c); });
  return set;
}

void part1(const Lines &lines) {
  std::unordered_set<char> seen;
  uint32_t prioSum{0};
  for (const auto &line : lines) {
    {
      const auto sv = std::string_view(line.c_str(), line.size() / 2);
      std::for_each(sv.begin(), sv.end(),
                    [&seen](const auto &c) { seen.insert(c); });
    }
    {
      const auto sv = std::string_view(line.c_str() + line.size() / 2);
      std::any_of(sv.begin(), sv.end(), [&seen, &prioSum](const auto &c) {
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

void part2(const Lines &lines) {
  uint32_t prioSum{0};
  std::vector<std::set<char>> seenSets;
  seenSets.reserve(3);
  for (size_t i = 0; i < lines.size(); i += 3) {
    seenSets.push_back(toSet(lines[i]));
    seenSets.push_back(toSet(lines[i + 1]));
    seenSets.push_back(toSet(lines[i + 2]));

    std::vector<char> intersect1_2;
    std::set_intersection(seenSets[0].begin(), seenSets[0].end(),
                          seenSets[1].begin(), seenSets[1].end(),
                          std::back_inserter(intersect1_2));

    std::vector<char> intersection;
    std::set_intersection(intersect1_2.begin(), intersect1_2.end(),
                          seenSets[2].begin(), seenSets[2].end(),
                          std::back_inserter(intersection));
    assert(intersection.size() == 1);
    prioSum += prioMap(intersection[0]);
    seenSets.clear();
  }
  std::cout << prioSum << std::endl;
}

int main(int /*argc*/, char **argv) {
  auto lines = read_lines(argv[1], "\n");
  part1(lines);
  part2(lines);

  return 0;
}
