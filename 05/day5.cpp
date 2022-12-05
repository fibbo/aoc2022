#include "aoc_lib.hpp"
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace pgl::aoc;

std::pair<std::vector<std::deque<char>>, size_t>
parseStackConfig(const Lines &lines) {
  std::vector<std::deque<char>> stacks;
  stacks.resize(9);
  size_t lineIndex = 0;
  for (const auto &line : lines) {
    if (line.empty()) {
      break;
    }
    ++lineIndex;
    auto index = line.find("[");
    while (index != std::string::npos) {
      const auto stackEntry = (++index - 1) / 4;
      stacks[stackEntry].push_front(line[index]);
      index = line.find("[", index);
    }
  }
  return {stacks, ++lineIndex};
}

struct StackOperation {
  size_t nElements;
  size_t sourceStack;
  size_t destinationStack;
};

StackOperation makeStackOperation(const std::string &line) {
  const auto tokens = split_line(line, " ");
  const auto nElements = std::stoull(tokens[1]);
  const auto sourceStack = std::stoull(tokens[3]) - 1;
  const auto destinationStack = std::stoull(tokens[5]) - 1;
  return {nElements, sourceStack, destinationStack};
}

int main(int /*argc*/, char **argv) {
  const auto lines = read_lines(argv[1]);

  auto singleStackMove = [](std::vector<std::deque<char>> &stacks,
                            StackOperation &&op) {
    for (auto i = 0U; i < op.nElements; ++i) {
      stacks[op.destinationStack].push_back(stacks[op.sourceStack].back());
      stacks[op.sourceStack].pop_back();
    }
  };

  auto multiStackMove = [](std::vector<std::deque<char>> &stacks,
                           StackOperation &&op) {
    std::stack<char> tmpStack;
    for (auto i = 0U; i < op.nElements; ++i) {
      tmpStack.push(stacks[op.sourceStack].back());
      stacks[op.sourceStack].pop_back();
    }
    while (!tmpStack.empty()) {
      stacks[op.destinationStack].push_back(tmpStack.top());
      tmpStack.pop();
    }
  };

  auto printBackOfStacks = [](const std::vector<std::deque<char>> &stacks) {
    for (const auto &stack : stacks) {
      if (stacks.empty()) {
        continue;
      }
      std::cout << stack.back();
    }
    std::cout << std::endl;
  };

  auto stacks = parseStackConfig(lines);

  for (auto i = stacks.second; i < lines.size(); ++i) {
    singleStackMove(stacks.first, makeStackOperation(lines[i]));
  }
  printBackOfStacks(stacks.first);

  stacks = parseStackConfig(lines);
  for (auto i = stacks.second; i < lines.size(); ++i) {
    multiStackMove(stacks.first, makeStackOperation(lines[i]));
  }
  printBackOfStacks(stacks.first);

  return 0;
}
