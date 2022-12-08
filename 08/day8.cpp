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

enum class Direction {
  top_down,
  left_right,
  bottom_up,
  right_left,
};

class Grid {
public:
  Grid(std::vector<uint32_t> input, uint32_t width, uint32_t height)
      : data_(std::move(input))
      , width_(width)
      , height_(height) {
  }

  uint32_t operator[](uint32_t index) const {
    return data_[index];
  }


  uint32_t size() const {
    return data_.size();
  }

  uint32_t width() const {
    return width_;
  }

  uint32_t height() const {
    return height_;
  }

  std::vector<uint32_t> data() const {
    return data_;
  }

private:
  std::vector<uint32_t> data_;
  uint32_t width_;
  uint32_t height_;
};

uint32_t countVisibleTrees(const Grid& input) {
  std::unordered_set<uint32_t> seenTrees;
  const auto data = input.data();
  const auto directions = std::to_array<Direction>(
      {Direction::top_down,
       Direction::left_right,
       Direction::bottom_up,
       Direction::right_left});
  for (const auto& direction : directions) {
    switch (direction) {
    case Direction::top_down: {
      std::cout << "Top down" << std::endl;
      for (auto i = 0U; i < input.width() - 2; ++i) {
        uint32_t largestVisibleTree = input[i + 1];
        std::cout << "Largest visible tree: " << largestVisibleTree
                  << std::endl;
        for (const auto& value :
             data | ranges::views::enumerate |
                 ranges::views::drop(input.width() + i + 1) |
                 ranges::views::stride(input.width()) |
                 ranges::views::take(input.width() - 2)) {
          std::cout << value.first << " " << value.second << std::endl;
          if (value.second > largestVisibleTree) {
            if (!seenTrees.contains(value.first)) {
              seenTrees.insert(value.first);
              largestVisibleTree = value.second;
            }
            largestVisibleTree = value.second;
          }
        }
      }
      break;
    }

    case Direction::left_right: {
      std::cout << "Left right" << std::endl;
      for (auto i = 0U; i < input.height() - 2; ++i) {
        uint32_t largestVisibleTree = input[input.width() + i * input.width()];
        std::cout << "Largest visible tree: " << largestVisibleTree
                  << std::endl;
        for (const auto& value :
             data | ranges::views::enumerate |
                 ranges::views::drop(input.width() + i * input.width() + 1) |
                 ranges::views::take(input.width() - 2)) {
          std::cout << value.first << " " << value.second << std::endl;
          if (value.second > largestVisibleTree) {
            if (!seenTrees.contains(value.first)) {
              seenTrees.insert(value.first);
              largestVisibleTree = value.second;
            }
            largestVisibleTree = value.second;
          }
        }
      }
    } break;

    case Direction::bottom_up:
      for (auto i = 0U; i < input.width() - 2; ++i) {
        uint32_t largestVisibleTree = input[input.size() - 2 - i];
        for (const auto& value :
             data | ranges::views::enumerate | ranges::views::reverse |
                 ranges::views::drop((1 + i) + input.width()) |
                 ranges::views::stride(input.width()) |
                 ranges::views::take(input.width() - 2)) {
          if (value.second > largestVisibleTree) {
            if (!seenTrees.contains(value.first)) {
              seenTrees.insert(value.first);
              largestVisibleTree = value.second;
            }
            largestVisibleTree = value.second;
          }
        }
      }
      break;
    case Direction::right_left:
      for (auto i = 0U; i < input.width() - 2; ++i) {
        uint32_t largestVisibleTree =
            input[input.size() - (1 + input.width()) - i * input.width()];
        for (const auto& value :
             data | ranges::views::enumerate | ranges::views::reverse |
                 ranges::views::drop(input.width() + i * input.width() + 1) |
                 ranges::views::take(input.width() - 2)) {
          std::cout << value.first << " " << value.second << std::endl;
          if (value.second > largestVisibleTree) {
            if (!seenTrees.contains(value.first)) {
              seenTrees.insert(value.first);
              largestVisibleTree = value.second;
            }
            largestVisibleTree = value.second;
          }
        }
      }
      break;
    }
  }
  return seenTrees.size();
}


int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "08/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);
  const auto width = lines[0].size();
  const auto height = lines.size();
  const auto gridSize = width * height;

  auto visible = 2 * width + 2 * height - 4;
  std::vector<uint32_t> trees;

  for (const auto& line : lines) {
    for (const auto& c : line) {
      trees.push_back(c - '0');
    }
  }
  for (auto i = 0U; i < gridSize; ++i) {
    std::cout << trees[i];
    if ((i + 1) % width == 0) {
      std::cout << std::endl;
    }
  }
  Grid grid(std::move(trees), width, height);

  visible += countVisibleTrees(grid);
  std::cout << visible << std::endl;

  return 0;
}
