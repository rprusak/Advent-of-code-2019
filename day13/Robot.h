#ifndef DAY11_ROBOT_H
#define DAY11_ROBOT_H

#include <map>
#include <utility>

#include "RobotInterface.h"

class Robot : public RobotInterface {
 public:
  void setX(long x) override;
  void setY(long y) override;
  void setTileId(long id) override;
  void draw() override;

  unsigned getBlockTilesCount() const;
  void print() const;

  long getScore() const;

  long getInput() override;

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
  };

  enum class TileId { EMPTY, WALL, BLOCK, PADDLE, BALL };

  long _score{0};
  long _x{0};
  long _y{0};
  TileId _tileId{TileId::EMPTY};
  std::map<Point, TileId> _grid;
};

#endif  // DAY11_ROBOT_H
