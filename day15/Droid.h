#ifndef DAY15_DROID_H
#define DAY15_DROID_H

#include <algorithm>
#include <map>
#include <random>

#include "ProgramInterface.h"

class Droid {
 public:
  explicit Droid(ProgramInterface& program);

  void run();
  void print() const;
  long getShortestPathLength();
  long fillWithOxygen();

 private:
  struct Point {
    long x{0};
    long y{0};

    bool operator<(const Point& p) const {
      if (this->x < p.x)
        return true;
      else if (p.x < this->x)
        return false;
      else
        return this->y < p.y;
    }

    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  };

  enum class FieldType { EMPTY, WALL, OXYGEN };

  class VisitedStatus : public std::map<Point, bool> {
   public:
    bool hasUnvisited() {
      auto isNotVisited = [](const std::map<Point, bool>::value_type& p) {
        return !p.second;
      };

      return std::any_of(begin(), end(), isNotVisited);
    }
  };

  using Direction = std::pair<Point, long>;

  ProgramInterface& _program;
  Point _currentPosition;
  Point _oxygenPoint;
  std::map<Point, FieldType> _area;
  VisitedStatus _visitedStatus;
  std::random_device _dev;
  std::mt19937 _rng;

  bool hasNotDiscoveredFieldsAround() const;
  std::vector<Direction> getDirections() const;
  std::vector<Direction> getNotDiscoveredFieldsAround() const;
  std::vector<Direction> getMovableFieldsAround() const;
  long getOppositeDirection(long direction) const;
  Droid::Direction getMoveDirection();
  FieldType getFieldType(long value) const;

  bool isFullyFilled() const;
  std::vector<Point> getOxygenPoints() const;
  std::vector<Point> getEmptyFieldsAround() const;
};

#endif  // DAY15_DROID_H
