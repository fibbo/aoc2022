#include "aoc_lib.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <range/v3/view/drop.hpp>
#include <string>
#include <vector>

using namespace pgl::aoc;

struct File {
  File(const std::string& name, bool isDirectory, uint64_t size)
      : name{name}
      , isDirectory{isDirectory}
      , size{size} {
  }
  std::string name;
  bool isDirectory;
  uint64_t size;
  File* parent{nullptr};
  std::vector<File> children;
};

void parseFileSystem(const Lines& lines, File* root) {
  File* parent{root};
  for (const auto& line : lines | ranges::views::drop(1)) {
    // Move one folder up
    if (line == "$ cd ..") {
      parent = parent->parent;
      continue;
    }

    // About to list directory
    if (line == "$ ls") {
      continue;
    }

    // $ cd <path>
    // This is always follwed by a $ ls
    // Make the <path> File the parent for the next $ ls
    // NB: $ cd / has been dropped from the input
    if (line.starts_with("$ cd ")) {
      const auto name = line.substr(5);
      const auto it = std::find_if(
          parent->children.begin(),
          parent->children.end(),
          [&name](const File& file) { return file.name == name; });
      parent = &(*it);
      continue;
    }

    const auto tokens = split_line(line, " ");
    if (tokens[0] == "dir") {
      parent->children.emplace_back(tokens[1], true, 0);
      parent->children.back().parent = parent;
    } else {
      parent->children.emplace_back(tokens[1], false, std::stoul(tokens[0]));
    }
  }
}

void calculateFolderSize(File* root) {
  for (auto& child : root->children) {
    if (child.isDirectory) {
      calculateFolderSize(&child);
    }
    root->size += child.size;
  }
}

template <typename F>
void traverseFileSystem(File* root, F&& f) {
  for (auto& child : root->children) {
    if (child.isDirectory) {
      f(child);
      traverseFileSystem(&child, f);
    }
  }
}

int main(int argc, char** argv) {
  std::string fileName;
  if (argc == 2) {
    fileName = argv[1];
  } else {
    fileName = "07/input_example.txt";
  }

  bool runExample{false};
  if (fileName.find("example") != std::string::npos) {
    runExample = true;
  }

  const auto lines = read_lines(fileName);

  File root("/", true, 0);
  parseFileSystem(lines, &root);
  calculateFolderSize(&root);

  uint64_t size{0};
  const auto hasMaxSize = [&size](const File& file) {
    if (file.isDirectory && file.size <= 100000) {
      size += file.size;
    }
  };
  traverseFileSystem(&root, hasMaxSize);
  std::cout << size << std::endl;
  if (runExample) {
    assert(size == 95437);
  } else {
    assert(size == 1428881);
  }

  constexpr uint64_t maxSize{70000000U};
  constexpr uint64_t minSpaceNeeded{30000000U};
  constexpr uint64_t useableSpace = maxSize - minSpaceNeeded;
  const auto spaceNeeded = root.size - useableSpace;
  std::vector<uint64_t> candidatesToDelete;
  const auto wouldFreeEnoughSpace = [&candidatesToDelete,
                                     spaceNeeded](const File& file) {
    if (file.isDirectory && file.size >= spaceNeeded) {
      candidatesToDelete.push_back(file.size);
    }
  };
  traverseFileSystem(&root, wouldFreeEnoughSpace);
  std::sort(candidatesToDelete.begin(), candidatesToDelete.end());
  if (runExample) {
    assert(candidatesToDelete.front() == 24933642);
  } else {
    assert(candidatesToDelete.front() == 10475598);
  }
  std::cout << candidatesToDelete.front() << std::endl;

  return 0;
}
