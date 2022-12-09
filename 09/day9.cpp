#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <unordered_set>
#include <vector>

using namespace pgl::aoc;

struct Move {
  char direction;
  int64_t distance;
};

std::istream& operator>>(std::istream& is, Move& move) {
  is >> move.direction >> move.distance;
  return is;
}

class Rope {
public:
  explicit Rope(uint32_t numberKnots)
      : knots_{std::vector<Point>(numberKnots)}
      , head_{knots_.front()}
      , tail_{knots_.back()} {
  }

  void move(const Move& move) {
    for (auto i = 0U; i < move.distance; ++i) {
      switch (move.direction) {
      case 'U':
        head_.y += 1;
        break;
      case 'D':
        head_.y -= 1;
        break;
      case 'L':
        head_.x -= 1;
        break;
      case 'R':
        head_.x += 1;
        break;
      }
      moveKnots();
      visitedPoints_.insert(knots_.back());
    }
  }

  size_t visitedPoints() const {
    return visitedPoints_.size();
  }

private:
  void moveKnots() {
    for (auto i = 0U; i < knots_.size() - 1; ++i) {
      moveTwoKnots(knots_[i], knots_[i + 1]);
    }
  }

  void moveTwoKnots(Point& head, Point& tail) {
    const auto xDiff = head.x - tail.x;
    const auto yDiff = head.y - tail.y;
    if (std::abs(xDiff) <= 1 && std::abs(yDiff) <= 1) {
      return;
    }
    if (xDiff > 1) {
      tail.x += 1;
    } else if (xDiff < -1) {
      tail.x -= 1;
    }
    if (yDiff > 1) {
      tail.y += 1;
    } else if (yDiff < -1) {
      tail.y -= 1;
    }
    if (std::abs(xDiff) + std::abs(yDiff) == 3) {
      // Tail needs to move diagonally
      if (std::abs(xDiff) == 2) {
        // Align in x direction
        tail.y = head.y;

      } else {
        // Align in y direction
        tail.x = head.x;
      }
    }
  }

  std::unordered_set<Point> visitedPoints_;
  std::vector<Point> knots_;
  Point& head_;
  Point& tail_;
};

int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "09/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);

  std::unordered_set<Point> points;
  Rope rope(2);
  Rope rope2(10);
  Move m;
  for (const auto& line : lines) {
    std::istringstream is(line);
    while (is >> m) {
      rope.move(m);
      rope2.move(m);
    }
  }

  std::cout << rope.visitedPoints() << std::endl;
  std::cout << rope2.visitedPoints() << std::endl;

  return 0;
}
