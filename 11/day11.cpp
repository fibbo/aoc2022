#include "aoc_lib.hpp"

#include <algorithm>
#include <array>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
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

  friend std::istream& operator>>(std::istream& is, Monkey& monkey) {
    std::string line(std::istreambuf_iterator<char>(is), {});
    auto tokens = split_line(line, "\n");
    tokens.erase(tokens.begin());
    for (auto& token : tokens) {
      auto info = token.substr(token.find(":") + 1);
      boost::trim(token);
      if (token.starts_with("Starting")) {
        const auto items = split_line(info, ",");
        for (auto& item : items) {
          monkey.items_.push_back(std::stoull(item));
        }
      }
      if (token.starts_with("Operation")) {
        if (line.find("old * old") != std::string::npos) {
          monkey.type_ = MonkeyType::squarer;
          continue;
        }
        monkey.opValue_ = std::stoul(split_line(info, " ")[5]);
        if (line.find("+") != std::string::npos) {
          monkey.type_ = MonkeyType::adder;
        } else {
          monkey.type_ = MonkeyType::multiplier;
        }
      }

      if (token.starts_with("Test")) {
        const auto testTokens = split_line(info, " ");
        monkey.throwDivisor_ = std::stoul(testTokens[3]);
      }

      if (token.starts_with("If true")) {
        monkey.monkeyTrue_ = std::stoul(split_line(info, " ")[4]);
      }
      if (token.starts_with("If false")) {
        monkey.monkeyFalse_ = std::stoul(split_line(info, " ")[4]);
      }
    }
    return is;
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
  const auto file = read_file(open_file(fileName)).str();
  std::vector<std::string> monkeyLines;
  auto re = boost::regex("\n\n");

  boost::split_regex(monkeyLines, file, re);
  std::vector<Monkey> monkeys;
  uint64_t superModulo{1};
  for (const auto& line : monkeyLines) {
    Monkey monkey;
    std::stringstream ss(line);
    ss >> monkey;
    superModulo *= monkey.throwDivisor_;
    monkeys.push_back(monkey);
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
