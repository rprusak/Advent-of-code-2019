#include <iostream>
#include <map>

#include "Program.h"
#include "util.h"

struct Point {
  long _x{0};
  long _y{0};

  bool operator==(const Point& p) const { return _x == p._x && _y == p._y; }

  bool operator<(const Point& p) const {
    if (_x < p._x)
      return true;
    else if (p._x < _x)
      return false;
    else
      return _y < p._y;
  }
};

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid program arguments" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto intcodeProgram = util::readInput(argv[1]).front();

  std::map<Point, char> area;

  for (long x = 0; x < 200; x++) {
    for (long y = 0; y < 200; y++) {
      Program p{intcodeProgram};
      if (p.run(x, y) == 1)
        area[Point{x, y}] = '#';
      else
        area[Point{x, y}] = '.';
    }
  }

  for (long y = 0; y < 200; y++) {
    for (long x = 0; x < 200; x++) {
      std::cout << area[Point{x, y}];
    }
    std::cout << std::endl;
  }

  return 0;
}
