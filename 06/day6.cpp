#include "aoc_lib.hpp"

using namespace pgl::aoc;

int main(int argc, char **argv) {
  Lines lines;
  if (argc == 2) {
    lines = read_lines(argv[1]);
  } else {
    lines = read_lines("input.txt");
  }
  return 0;
}
