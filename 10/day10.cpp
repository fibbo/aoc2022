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


std::istream& operator>>(std::istream& is, Op& op) {
  std::string opString;
  is >> opString;
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

class Cpu {
public:
  Cpu()
      : cycle_{0}
      , register_{1}
      , signalStrength_{0} {
  }

  void increaseCycle() {
    ++cycle_;
    if (currentOp_ == nullptr) {
      currentOp_ = &ops_[0];
    }
    // std::cout << "Cycle: " << cycle_ << " Register: " << register_ <<
    // std::endl; std::cout << "Current op: " <<
    // static_cast<int>(currentOp_->type_) << " "
    //           << currentOp_->x_ << std::endl;

    // during the cycle
    if ((cycle_ + 20) % 40 == 0) {
      signalStrength_ += register_ * cycle_;
      std::cout << "Signal strength: " << signalStrength_ << std::endl;
    }

    // Check if the register_ is covering the pixel where the current cycle is
    // drawing

    if (currentOp_->execute(*this)) {
      ops_.erase(ops_.begin());
      currentOp_ = nullptr;
    }

    // std::cout << "After Cycle: " << cycle_ << " Register: " << register_
    //<< std::endl;
  }

  void run() {
    while (!ops_.empty()) {
      increaseCycle();
    }
  }

  void addOp(Op op) {
    ops_.push_back(std::move(op));
  }

  void add_x(int64_t x) {
    register_ += x;
  }

private:
  uint64_t cycle_;
  int64_t register_;
  int64_t signalStrength_;
  Op* currentOp_;
  std::deque<Op> ops_;
};

Op::Op(OpType type, int64_t x)
    : type_(type)
    , x_(x) {
}
bool Op::execute(Cpu& cpu) {
  ++cycleCount_;
  switch (type_) {
  case OpType::addx:
    if (cycleCount_ == 2) {
      cpu.add_x(x_);
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
    fileName = "x/input_example.txt";
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


  return 0;
}
