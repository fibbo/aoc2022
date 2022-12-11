#include "aoc_lib.hpp"

#include <_types/_uint64_t.h>
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

using namespace pgl::aoc;

auto adder = [](auto a, auto b) { return a + b; };
auto multiplier = [](auto a, auto b) { return a * b; };
auto square = [](auto a) { return a * a; };

struct ItemToMonkey {
  uint64_t item;
  uint32_t monkey;
};

enum class MonkeyType { adder, multiplier, squarer };

struct Monkey {
public:
  Monkey() = default;
  Monkey(
      std::vector<uint64_t> items,
      uint32_t throwDivisor,
      MonkeyType type,
      uint32_t opValue,
      uint32_t monkeyTrue,
      uint32_t monkeyFalse)
      : items_(std::move(items))
      , throwDivisor_(throwDivisor)
      , type_{type}
      , opValue_{opValue}
      , monkeyTrue_{monkeyTrue}
      , monkeyFalse_{monkeyFalse} {
  }

  void printMonkey() {
    std::cout << "Monkey: " << std::endl;
    std::cout << "  items: ";
    for (auto item : items_) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << "  throwDivisor: " << throwDivisor_ << std::endl;
    std::cout << "  type: " << static_cast<uint32_t>(type_) << std::endl;
    std::cout << "  opValue: " << opValue_ << std::endl;
    std::cout << "  monkeyTrue: " << monkeyTrue_ << std::endl;
    std::cout << "  monkeyFalse: " << monkeyFalse_ << std::endl;
  }

  std::vector<ItemToMonkey> inspectItems(bool lowerWorry = true) {
    std::vector<ItemToMonkey> itemsToMonkey;
    for (auto& item : items_) {
      ++inspectionCount_;
      switch (type_) {
      case MonkeyType::adder:
        item = adder(item, opValue_);
        break;
      case MonkeyType::multiplier:
        item = multiplier(item, opValue_);
        break;
      case MonkeyType::squarer:
        item = square(item);
        break;
      }
      if (lowerWorry) {
        item /= 3;
      } else {
        item %= superModulo_;
      }
      if (item % throwDivisor_ == 0) {
        itemsToMonkey.push_back({item, monkeyTrue_});
      } else {
        itemsToMonkey.push_back({item, monkeyFalse_});
      }
    }
    items_.clear();
    return itemsToMonkey;
  }

  std::vector<uint64_t> items_;
  uint32_t throwDivisor_;
  uint64_t superModulo_{1};
  MonkeyType type_;
  uint32_t opValue_;
  uint32_t monkeyTrue_{0};
  uint32_t monkeyFalse_{0};
  uint64_t inspectionCount_{0};
};

int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "11/input_example.txt";
  }

  [[maybe_unused]] bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);
  std::vector<Monkey> monkeys;
  Monkey monkey;
  uint64_t superModulo{1};
  for (const auto& line : lines) {

    if (line.empty()) {
      continue;
    }
    if (line.starts_with("Monkey")) {
      continue;
    }
    if (line.find("  Starting items: ") != std::string::npos) {
      const auto items = line.substr(18);
      const auto tokens = split_line(items, ",");
      for (const auto& token : tokens) {
        monkey.items_.push_back(std::stoul(token));
      }
    }
    if (line.starts_with("  Operation:")) {
      const auto tokens = split_line(line, " ");
      if (line.find("+") != std::string::npos) {
        monkey.type_ = MonkeyType::adder;
        monkey.opValue_ = std::stoul(tokens[7]);
      } else if (line.find("old * old") != std::string::npos) {
        monkey.type_ = MonkeyType::squarer;
      } else {
        monkey.type_ = MonkeyType::multiplier;
        monkey.opValue_ = std::stoul(tokens[7]);
      }
    }
    if (line.find("Test:") != std::string::npos) {
      const auto tokens = split_line(line, " ");

      monkey.throwDivisor_ = std::stoul(tokens[5]);
      std::cout << "throwDivisor: " << monkey.throwDivisor_ << std::endl;
      superModulo *= monkey.throwDivisor_;
    }
    if (line.find("true") != std::string::npos) {
      const auto tokens = split_line(line, " ");
      monkey.monkeyTrue_ = std::stoul(tokens[9]);
    }
    if (line.find("false") != std::string::npos) {
      const auto tokens = split_line(line, " ");
      monkey.monkeyFalse_ = std::stoul(tokens[9]);
      monkeys.emplace_back(std::move(monkey));
      monkey.inspectionCount_ = 0;
      monkey.opValue_ = 0;
    }
  }
  for (auto& monkey : monkeys) {
    monkey.superModulo_ = superModulo;
  }

  for (auto i = 0U; i < 10000; ++i) {
    for (auto& monkey : monkeys) {
      auto itemToMonkey = monkey.inspectItems(false);
      for (auto& itm : itemToMonkey) {
        monkeys[itm.monkey].items_.push_back(itm.item);
      }
    }
  }

  std::vector<uint64_t> inspectionCounts;
  for (auto& monkey : monkeys) {
    std::cout << "Monkey: " << monkey.inspectionCount_ << std::endl;
    inspectionCounts.push_back(monkey.inspectionCount_);
  }
  std::sort(inspectionCounts.begin(), inspectionCounts.end(), std::greater<>());
  uint64_t result = inspectionCounts[0] * inspectionCounts[1];
  std::cout << result << std::endl;


  return 0;
}
