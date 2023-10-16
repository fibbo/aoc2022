#include "aoc_lib.hpp"
#include "range/v3/action/transform.hpp"
#include "range/v3/iterator/operations.hpp"
#include "range/v3/view/enumerate.hpp"
#include "range/v3/view/for_each.hpp"
#include "range/v3/view/remove_if.hpp"
#include "range/v3/view/reverse.hpp"
#include "range/v3/view/transform.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <range/v3/all.hpp>
#include <unordered_set>
#include <vector>

using namespace pgl::aoc;

class Grid
{
public:
  Grid(std::vector<uint32_t> input, uint32_t width, uint32_t height)
      : data_(std::move(input))
      , width_(width)
      , height_(height)
  {
  }

  uint32_t operator[](uint32_t index) const
  {
    return data_[index];
  }

  uint32_t get(uint32_t x, uint32_t y) const
  {
    return data_[y * width_ + x];
  }


  uint32_t size() const
  {
    return data_.size();
  }

  uint32_t width() const
  {
    return width_;
  }

  uint32_t height() const
  {
    return height_;
  }

  const std::vector<uint32_t>& data() const
  {
    return data_;
  }

private:
  std::vector<uint32_t> data_;
  uint32_t width_;
  uint32_t height_;
};

template <typename T>
auto forwardRange = [](T range, uint32_t drop, uint32_t stride, uint32_t take)
{
  return range | ranges::views::enumerate | ranges::views::drop(drop) |
         ranges::views::stride(stride) | ranges::views::take(take);
};

template <typename T>
auto reverseRange = [](T range, uint32_t drop, uint32_t stride, uint32_t take)
{
  return range | ranges::views::enumerate | ranges::views::reverse |
         ranges::views::drop(drop) | ranges::views::stride(stride) |
         ranges::views::take(take);
};

enum class Direction
{
  top_down,
  left_right,
  bottom_up,
  right_left,
};

uint32_t countVisibleTrees(const Grid& input)
{
  const auto& data = input.data();
  const auto directions = std::to_array<Direction>(
      {Direction::top_down,
       Direction::left_right,
       Direction::bottom_up,
       Direction::right_left});

  std::unordered_set<uint32_t> seenTrees;
  auto isLargestTreeSofar =
      [&seenTrees](uint32_t& largestTree, const auto& tree)
  {
    if (tree.second > largestTree)
    {
      if (!seenTrees.contains(tree.first))
      {
        seenTrees.insert(tree.first);
        largestTree = tree.second;
      }
      largestTree = tree.second;
    }
  };

  for (const auto& direction : directions)
  {
    switch (direction)
    {
    case Direction::top_down:
    {
      for (auto i = 0U; i < input.width() - 2; ++i)
      {
        uint32_t largestVisibleTree = input[i + 1];
        for (const auto& value : forwardRange<decltype(data)>(
                 data,
                 input.width() + 1 + i,
                 input.width(),
                 input.height() - 2))
        {
          isLargestTreeSofar(largestVisibleTree, value);
        }
      }
      break;
    }

    case Direction::left_right:
    {
      for (auto i = 0U; i < input.height() - 2; ++i)
      {
        uint32_t largestVisibleTree = input[input.width() + i * input.width()];
        for (const auto& value : forwardRange<decltype(data)>(
                 data,
                 input.width() + 1 + i * input.width(),
                 1,
                 input.width() - 2))
        {
          isLargestTreeSofar(largestVisibleTree, value);
        }
      }
    }
    break;

    case Direction::bottom_up:
      for (auto i = 0U; i < input.width() - 2; ++i)
      {
        uint32_t largestVisibleTree = input[input.size() - 2 - i];
        for (const auto& value : reverseRange<decltype(data)>(
                 data,
                 (1 + i) + input.width(),
                 input.width(),
                 input.width() - 2))
        {
          isLargestTreeSofar(largestVisibleTree, value);
        }
      }
      break;
    case Direction::right_left:
      for (auto i = 0U; i < input.width() - 2; ++i)
      {
        uint32_t largestVisibleTree =
            input[input.size() - (1 + input.width()) - i * input.width()];
        for (const auto& value : reverseRange<decltype(data)>(
                 data,
                 input.width() + i * input.width() + 1,
                 1,
                 input.width() - 2))
        {
          isLargestTreeSofar(largestVisibleTree, value);
        }
      }
      break;
    }
  }
  return seenTrees.size();
}

uint32_t getScenicScore(const Grid& input)
{

  uint32_t scenicScore{0};
  for (auto j = 1U; j < input.height() - 1; ++j)
  {
    for (auto i = 1U; i < input.width() - 1; ++i)
    {
      // look left for taller tree
      uint32_t leftFactor{0};
      int32_t k = i - 1;
      while (k >= 0)
      {
        ++leftFactor;
        if (input.get(k, j) < input.get(i, j))
        {
          --k;
          continue;
        }
        break;
      }

      // look right for taller tree
      uint32_t rightFactor{0};
      k = i + 1;
      while (k < static_cast<int32_t>(input.width()))
      {
        ++rightFactor;
        if (input.get(k, j) < input.get(i, j))
        {
          ++k;
          continue;
        }
        break;
      }

      // look up for taller tree
      uint32_t upFactor{0};
      k = j - 1;
      while (k >= 0)
      {
        ++upFactor;
        if (input.get(i, k) < input.get(i, j))
        {
          --k;
          continue;
        }
        break;
      }

      // look down for taller tree
      uint32_t downFactor{0};
      k = j + 1;
      while (k < static_cast<int32_t>(input.height()))
      {
        ++downFactor;
        if (input.get(i, k) < input.get(i, j))
        {
          ++k;
          continue;
        }
        break;
      }
      if (upFactor * downFactor * leftFactor * rightFactor > scenicScore)
      {
        scenicScore = upFactor * downFactor * leftFactor * rightFactor;
      }
    }
  }
  return scenicScore;
}

int main(int argc, char** argv)
{
  std::string fileName;
  if (argc == 2)
  {
    fileName = argv[1];
  }
  else
  {
    fileName = "08/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos)
  {
    runExample = true;
  }

  const auto lines = read_lines(fileName);
  const auto width = lines[0].size();
  const auto height = lines.size();
  const auto gridSize = width * height;

  // Trees at the border are visible
  auto visible = 2 * width + 2 * height - 4;

  std::vector<uint32_t> trees;

  for (const auto& line : lines)
  {
    for (const auto& c : line)
    {
      trees.push_back(c - '0');
    }
  }

  if (runExample)
  {
    for (auto i = 0U; i < gridSize; ++i)
    {
      std::cout << trees[i];
      if ((i + 1) % width == 0)
      {
        std::cout << std::endl;
      }
    }
  }
  Grid grid(std::move(trees), width, height);

  visible += countVisibleTrees(grid);
  std::cout << visible << std::endl;

  std::cout << getScenicScore(grid) << std::endl;

  return 0;
}
