#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <unordered_map>

#include "util.h"

struct Point {
  int x;
  int y;
};

struct Line {
  int xA{0};
  int yA{0};
  int xB{0};
  int yB{0};

  bool isVertical() const { return xA == 0 && yA == 0 && xB == 0 && yB == 0; }

  bool pointIsOnLine(const Point& p) const {
    if (xA == xB) {  // pionowa
      if (p.x != xA) return false;

      auto minY = std::min(yA, yB);
      auto maxY = std::max(yA, yB);

      return minY < p.y && maxY > p.y;

    } else if (yA == yB) {  // pozioma
      if (p.y != yA) return false;

      auto minX = std::min(xA, xB);
      auto maxX = std::max(xA, xB);

      return minX < p.x && p.x < maxX;
    } else {
      auto minY = std::min(yA, yB);
      auto maxY = std::max(yA, yB);

      if (!(minY < p.y && maxY > p.y)) return false;

      auto minX = std::min(xA, xB);
      auto maxX = std::max(xA, xB);

      if (!(minX < p.x && p.x < maxX)) return false;

      return ((p.y - yA) * (xB - xA) - (yB - yA) * (p.x - xA)) == 0;
    }
  }
};

std::vector<Point> convertToPoints(
    const std::vector<std::string>& programInput) {
  std::vector<Point> points;

  for (int y = 0; y < programInput.size(); y++) {
    for (int x = 0; x < programInput[y].size(); x++) {
      if (programInput[y][x] == '#') points.push_back(Point{x, y});
    }
  }

  return points;
}

Line findLineBetweenPoints(const Point& sourcePoint,
                           const Point& destinationPoint) {
  Line l;

  l.xA = sourcePoint.x;
  l.yA = sourcePoint.y;
  l.xB = destinationPoint.x;
  l.yB = destinationPoint.y;

  return l;
}

unsigned findBestPoint(const std::vector<Point>& points) {
  std::unordered_map<const Point*, unsigned> pointCounters;

  for (auto sourcePointIt = points.begin(); sourcePointIt != points.end();
       sourcePointIt++) {
    for (auto destinationPointIt = sourcePointIt + 1;
         destinationPointIt != points.end(); destinationPointIt++) {
      auto line = findLineBetweenPoints(*sourcePointIt, *destinationPointIt);

      bool pointFound{false};
      for (const auto& point : points) {
        if (line.pointIsOnLine(point)) {
          pointFound = true;
          break;
        }
      }

      if (pointFound) continue;

      pointCounters[&(*sourcePointIt)] += 1;
      pointCounters[&(*destinationPointIt)] += 1;
    }
  }

  unsigned res{0};
  for (const auto& [point, counter] : pointCounters) {
    if (counter > res) {
      res = counter;
    }
  }

  return res;
}

std::set<const Point*> findBestPoint2(const std::vector<Point>& points) {
  std::unordered_map<const Point*, unsigned> pointCounters;
  std::unordered_map<const Point*, std::set<const Point*>> seenPoints;

  for (auto sourcePointIt = points.begin(); sourcePointIt != points.end();
       sourcePointIt++) {
    for (auto destinationPointIt = sourcePointIt + 1;
         destinationPointIt != points.end(); destinationPointIt++) {
      auto line = findLineBetweenPoints(*sourcePointIt, *destinationPointIt);

      bool pointFound{false};
      for (const auto& point : points) {
        if (line.pointIsOnLine(point)) {
          pointFound = true;
          break;
        }
      }

      if (pointFound) continue;

      pointCounters[&(*sourcePointIt)] += 1;
      pointCounters[&(*destinationPointIt)] += 1;
      seenPoints[&(*sourcePointIt)].insert(&(*destinationPointIt));
      seenPoints[&(*destinationPointIt)].insert(&(*sourcePointIt));
    }
  }

  unsigned res{0};
  std::set<const Point*> resSet;

  for (const auto& [point, counter] : pointCounters) {
    if (counter > res) {
      res = counter;
      resSet = seenPoints[point];
    }
  }

  return resSet;
}

double theta(const Point& station, const Point& asteroid) {
  if (station.x == asteroid.x) {
    if (asteroid.y < station.y)
      return 0;
    else
      return M_PI;
  } else if (station.y == asteroid.y) {
    if (asteroid.x < station.x)
      return M_PI + M_PI_2;
    else
      return M_PI_2;
  } else {
    if (asteroid.x > station.x && asteroid.y < station.y) {
      return atan2(asteroid.x - station.x, station.y - asteroid.y);
    } else if (asteroid.x > station.x && asteroid.y > station.y) {
      return M_PI - atan2(asteroid.x - station.x, asteroid.y - station.y);
    } else if (asteroid.x < station.x && asteroid.y > station.y) {
      return M_PI + atan2(station.x - asteroid.x, asteroid.y - station.y);
    } else {
      return 2 * M_PI - atan2(station.x - asteroid.x, station.y - asteroid.y);
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid arguments" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto input = util::readInput(argv[1]);
  auto points = convertToPoints(input);

  auto resSet = findBestPoint2(points);
  std::vector<const Point*> pointsVector;

  for (const auto* p : resSet) pointsVector.push_back(p);

  Point bestPoint{20, 20};

  auto comparator = [bestPoint](const Point* p1, const Point* p2) {
    return theta(bestPoint, *p1) < theta(bestPoint, *p2);
  };

  std::sort(pointsVector.begin(), pointsVector.end(), comparator);

  std::cout << pointsVector[199]->x << " " << pointsVector[199]->y << std::endl;

  return 0;
}
