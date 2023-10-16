#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>

using namespace pgl::aoc;

enum class OpType
{
  addx,
  noop,
};

class Cpu;

class Op
{
public:
  Op(OpType, int64_t);
  Op() = default;
  bool execute(Cpu&);

private:
  friend std::istream& operator>>(std::istream&, Op&);
  friend class Cpu;
  OpType type_;
  int64_t x_{0};
  short cycleCount_;
};

class Cpu
{
public:
  Cpu();

  void cycle();
  void run();
  void addOp(Op&& op);
  void addX(int64_t x);
  void printScreen();

private:
  bool cursorWithinSprite() const;
  void checkSignalStrength();
  void drawPixel();

  Op* currentOp_;
  uint64_t cycle_;
  int64_t register_;
  int64_t signalStrength_;
  uint64_t displayWidth_;
  uint64_t displayHeight_;
  std::vector<char> screen_;
  std::deque<Op> ops_;
};

Cpu::Cpu()
    : currentOp_{nullptr}
    , cycle_{0}
    , register_{1}
    , signalStrength_{0}
    , displayWidth_{40}
    , displayHeight_{6}
    , screen_(displayWidth_ * displayHeight_, ' ')
{
}

void Cpu::cycle()
{
  ++cycle_;
  if (currentOp_ == nullptr)
  {
    currentOp_ = &ops_.front();
  }

  checkSignalStrength();
  drawPixel();

  if (currentOp_->execute(*this))
  {
    ops_.pop_front();
    currentOp_ = nullptr;
  }
}

void Cpu::run()
{
  while (!ops_.empty() || currentOp_ != nullptr)
  {
    cycle();
  }
}

void Cpu::addOp(Op&& op)
{
  ops_.push_back(std::move(op));
}

void Cpu::addX(int64_t x)
{
  register_ += x;
}

void Cpu::printScreen()
{
  for (auto i = 0U; i < displayWidth_ * displayHeight_; ++i)
  {
    if (i % displayWidth_ == 0)
    {
      std::cout << std::endl;
    }
    std::cout << screen_[i];
  }
  std::cout << std::endl;
}

bool Cpu::cursorWithinSprite() const
{
  const int64_t currentPixel = (cycle_ - 1) % displayWidth_;
  return currentPixel >= register_ - 1 && currentPixel <= register_ + 1;
}

void Cpu::checkSignalStrength()
{
  // For part 1
  if ((cycle_ + 20) % displayWidth_ == 0)
  {
    signalStrength_ += register_ * cycle_;
    std::cout << "Signal strength: " << signalStrength_ << std::endl;
  }
}

void Cpu::drawPixel()
{
  // Check if the register_ is covering the pixel where the current cycle is
  // drawing
  auto c = '.';
  const auto row = (cycle_ - 1) / displayWidth_;
  const auto col = (cycle_ - 1) % displayWidth_;
  if (cursorWithinSprite())
  {
    c = '#';
  }
  screen_[row * displayWidth_ + col] = c;
}

std::istream& operator>>(std::istream& is, Op& op)
{
  std::string opString;
  is >> opString;
  op.cycleCount_ = 0;
  if (opString == "noop")
  {
    op.type_ = OpType::noop;
  }
  else if (opString == "addx")
  {
    op.type_ = OpType::addx;
    is >> op.x_;
  }
  else
  {
    throw std::runtime_error("Invalid op");
  }
  return is;
}

Op::Op(OpType type, int64_t x)
    : type_(type)
    , x_(x)
{
}

// If the op is done, return true
bool Op::execute(Cpu& cpu)
{
  ++cycleCount_;
  switch (type_)
  {
  case OpType::addx:
    if (cycleCount_ == 2)
    {
      cpu.addX(x_);
      return true;
    }
    return false;
    break;
  case OpType::noop:
    return true;
    break;
  }
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
    fileName = "10/input_example.txt";
  }

  const auto lines = read_lines(fileName);

  Cpu cpu;
  for (const auto& line : lines)
  {
    Op op;
    std::istringstream iss(line);
    iss >> op;
    cpu.addOp(std::move(op));
  }

  cpu.run();
  cpu.printScreen();

  return 0;
}
