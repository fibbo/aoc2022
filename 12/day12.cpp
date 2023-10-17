#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace pgl::aoc;

class Grid
{
public:
  Grid(std::vector<std::string> const& lines)
      : width_{lines[0].size()}
      , height_{lines.size()}
  {
    grid_.resize(width_ * height_);
    for (auto i = 0u; i < lines.size(); i++)
    {
      for (auto j = 0u; j < lines[i].size(); j++)
      {
        const size_t index = i * width_ + j;
        if (lines[i][j] == 'S')
        {
          grid_[index] = 0;
        }
        else if (lines[i][j] == 'E')
        {
          grid_[index] = 26;
        }
        else
        {
          grid_[index] = convertCharToInt(lines[i][j]);
        }
      }
    }
  }

  void print() const
  {
    for (auto i = 0u; i < height_; i++)
    {
      for (auto j = 0u; j < width_; j++)
      {
        std::cout << grid_[i * width_ + j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<uint32_t> grid_;
  size_t width_;
  size_t height_;
};

int main(int argc, char** argv)
{
  std::string fileName;
  if (argc == 2)
  {
    fileName = argv[1];
  }
  else
  {
    fileName = "12/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos)
  {
    runExample = true;
  }

  const auto lines = read_lines(fileName);
  Grid g{lines};
  g.print();
  return 0;
}
