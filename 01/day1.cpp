#include "aoc_lib.hpp"

#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>

using namespace pgl::aoc;

void part1(const Lines& lines)
{
  uint32_t calCount{0};
  uint32_t bigGuyCal{0};

  for (const auto& line : lines)
  {
    if (!line.empty())
    {
      calCount += std::stoull(line);
    }
    else
    {
      if (calCount > bigGuyCal)
      {
        bigGuyCal = calCount;
      }
      calCount = 0;
    }
  }
  std::cout << bigGuyCal << std::endl;
}

void part2(const Lines& lines)
{
  std::vector<uint32_t> calCounts;
  uint32_t calCount{0};
  for (const auto& line : lines)
  {
    if (!line.empty())
    {
      calCount += std::stoull(line);
    }
    else
    {
      calCounts.push_back(calCount);
      calCount = 0;
    }
  }

  std::sort(
      calCounts.begin(),
      calCounts.end(),
      [](const auto& a, const auto& b) { return a > b; });
  const auto calories = std::accumulate(
      calCounts.begin(),
      std::next(calCounts.begin(), 3),
      0,
      [](const auto& a, const auto& b) { return a + b; });

  std::cout << calories << std::endl;
}

int main(int /*argc*/, char** argv)
{

  const auto lines = read_lines(argv[1]);
  part1(lines);
  part2(lines);

  std::string command{""};
  std::string manifest{"a,b,c,d,"};
  std::set<std::string> setCommand;
  std::set<std::string> setManifest;
  boost::split(setCommand, command, boost::is_any_of(","));
  boost::split(setManifest, manifest, boost::is_any_of(","));
  const auto includes = std::includes(
      setManifest.begin(),
      setManifest.end(),
      setCommand.begin(),
      setCommand.end());

  std::cout << includes << std::endl;
  const auto string = std::filesystem::read_symlink("/Users/philippg/OneDrive");
  std::cout << string.string() << std::endl;

  return 0;
}
