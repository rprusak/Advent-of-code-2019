#include <algorithm>
#include <iostream>
#include <regex>

#include "util.h"

class Point {
 public:
  Point(long x, long y, long z) : _x(x) /*, _y(y), _z(z) */ {
    _itinialx = x;
    //        _itinialy = y;
    //        _itinialz = z;
  }

  void move() {
    _x += _vx;
    //        _y += _vy;
    //        _z += _vz;
  }

  unsigned long getEnergy() {
    return 0;
    //        return (std::abs(_x) + std::abs(_y) + std::abs(_z)) *
    //                (std::abs(_vx) + std::abs(_vy) + std::abs(_vz));
  }

  void calculateVelocity(Point& secondPoint) {
    calculateVelocity(_x, _vx, secondPoint._x, secondPoint._vx);
    //        calculateVelocity(_y, _vy, secondPoint._y, secondPoint._vy);
    //        calculateVelocity(_z, _vz, secondPoint._z, secondPoint._vz);
  }

  bool hasZeroVelocity() const {
    return _vx == 00 /* && _vy == 0 && _vz == 0*/;
  }

  bool isInIntialState() const {
    return _x == _itinialx /*&& _y == _itinialy && _z == _itinialz*/;
  }

 private:
  long _x;
  //    long _y;
  //    long _z;

  long _itinialx;
  //    long _itinialy;
  //    long _itinialz;

  long _vx{0};
  //    long _vy{0};
  //    long _vz{0};

  void calculateVelocity(long& x1, long& vx1, long& x2, long& vx2) {
    if (x1 == x2) return;

    if (x1 > x2) {
      vx1 -= 1;
      vx2 += 1;
    } else {
      vx2 -= 1;
      vx1 += 1;
    }
  }
};

std::vector<Point> readPoints(const std::vector<std::string>& input) {
  std::regex pattern{R"#(^<x=(-?\d+),\sy=(-?\d+),\sz=(-?\d+)>$)#"};
  std::vector<Point> resultPoints;

  for (const auto& line : input) {
    std::smatch result;
    if (std::regex_match(line, result, pattern)) {
      auto x = std::stol(result[3].str());
      auto y = std::stol(result[2].str());
      auto z = std::stol(result[3].str());
      resultPoints.emplace_back(x, y, z);
    } else {
      std::cerr << "could not match line " << line << std::endl;
    }
  }

  return resultPoints;
}

unsigned long getTotalEnergy(std::vector<Point>& points, unsigned steps) {
  for (unsigned step = 0; step < steps; step++) {
    for (auto firstIt = points.begin(); firstIt != points.end(); firstIt++) {
      for (auto secondIt = firstIt + 1; secondIt != points.end(); secondIt++) {
        firstIt->calculateVelocity(*secondIt);
      }
    }

    for (auto& point : points) point.move();
  }

  unsigned long result{0};
  for (auto& point : points) result += point.getEnergy();

  return result;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid argumetns" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto input = util::readInput(argv[1]);
  auto points = readPoints(input);
  unsigned long s{0};

  auto hasZeroVelocity = [](const Point& p) { return p.hasZeroVelocity(); };

  auto isInInitialState = [](const Point& p) { return p.isInIntialState(); };

  while (true) {
    s++;
    for (auto firstIt = points.begin(); firstIt != points.end(); firstIt++) {
      for (auto secondIt = firstIt + 1; secondIt != points.end(); secondIt++) {
        firstIt->calculateVelocity(*secondIt);
      }
    }

    for (auto& point : points) point.move();

    bool zeroVelocity =
        std::all_of(points.begin(), points.end(), hasZeroVelocity);
    if (zeroVelocity) std::cout << "zero v" << std::endl;

    if (zeroVelocity &&
        std::all_of(points.begin(), points.end(), isInInitialState))
      break;
  }

  std::cout << s << std::endl;

  return 0;
}
