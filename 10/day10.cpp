#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace pgl::aoc;


enum class OpType {
  addx,
  noop,
};

class Cpu;

class Op {
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

class Cpu {
public:
  Cpu();

  void increaseCycle();
  void run();
  void addOp(Op op);
  void addX(int64_t x);
  void printScreen();

private:
  bool cursorWithinSprite() const;

  Op* currentOp_;
  uint64_t cycle_;
  int64_t register_;
  int64_t signalStrength_;
  std::vector<char> screen_;
  std::deque<Op> ops_;
};

Cpu::Cpu()
    : currentOp_{nullptr}
    , cycle_{0}
    , register_{1}
    , signalStrength_{0} {
  screen_.resize(240, '.');
}

void Cpu::increaseCycle() {
  ++cycle_;
  if (currentOp_ == nullptr) {
    currentOp_ = &ops_[0];
  }
  std::cout << "Cycle: " << cycle_ << " Register: " << register_ << std::endl;

  // during the cycle
  if ((cycle_ + 20) % 40 == 0) {
    signalStrength_ += register_ * cycle_;
    std::cout << "Signal strength: " << signalStrength_ << std::endl;
  }

  // Check if the register_ is covering the pixel where the current cycle is
  // drawing
  auto c = '.';
  const auto row = (cycle_ - 1) / 40;
  const auto col = (cycle_ - 1) % 40;
  if (cursorWithinSprite()) {
    c = '#';
  }
  std::cout << cycle_ << " drawing " << c << " at " << row << ", " << col
            << std::endl;
  screen_[row * 40 + col] = c;

  if (currentOp_->execute(*this)) {
    ops_.erase(ops_.begin());
    currentOp_ = nullptr;
  }
}


void Cpu::run() {
  while (!ops_.empty()) {
    increaseCycle();
  }
}

void Cpu::addOp(Op op) {
  ops_.push_back(std::move(op));
}

void Cpu::addX(int64_t x) {
  register_ += x;
}

void Cpu::printScreen() {
  for (auto i = 0; i < 240; ++i) {
    if (i % 40 == 0) {
      std::cout << std::endl;
    }
    std::cout << screen_[i];
  }
  std::cout << std::endl;
}

bool Cpu::cursorWithinSprite() const {
  const int64_t currentPixel = (cycle_ - 1) % 40U;
  std::cout << currentPixel << std::endl;
  return currentPixel >= register_ - 1 && currentPixel <= register_ + 1;
}


std::istream& operator>>(std::istream& is, Op& op) {
  std::string opString;
  is >> opString;
  op.cycleCount_ = 0;
  if (opString == "noop") {
    op.type_ = OpType::noop;
  } else if (opString == "addx") {
    op.type_ = OpType::addx;
    is >> op.x_;
  } else {
    throw std::runtime_error("Invalid op");
  }
  return is;
}

Op::Op(OpType type, int64_t x)
    : type_(type)
    , x_(x) {
}


bool Op::execute(Cpu& cpu) {
  ++cycleCount_;
  switch (type_) {
  case OpType::addx:
    if (cycleCount_ == 2) {
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

int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "10/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);

  Cpu cpu;
  for (const auto& line : lines) {
    Op op;
    std::istringstream iss(line);
    iss >> op;
    cpu.addOp(std::move(op));
  }

  cpu.run();
  cpu.printScreen();


  return 0;
}
