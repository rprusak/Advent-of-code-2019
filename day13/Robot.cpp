#include "Robot.h"

#include <algorithm>
#include <iostream>

void Robot::setX(long x) { _x = x; }

void Robot::setY(long y) { _y = y; }

void Robot::setTileId(long id) {
  if (_x == -1 && _y == 0) {
    _score = id;
    return;
  }

  switch (id) {
    case 0:
      _tileId = TileId::EMPTY;
      break;
    case 1:
      _tileId = TileId::WALL;
      break;
    case 2:
      _tileId = TileId::BLOCK;
      break;
    case 3:
      _tileId = TileId::PADDLE;
      break;
    case 4:
      _tileId = TileId::BALL;
      break;
    default:
      std::cerr << "invalid input" << std::endl;
  }
}

void Robot::draw() {
  if (!(_x == -1 && _y == 0)) {
    _grid[Point{_x, _y}] = _tileId;
  }
}

unsigned Robot::getBlockTilesCount() const {
  auto isBlockTile = [](const auto& p) { return p.second == TileId::BLOCK; };

  return std::count_if(_grid.begin(), _grid.end(), isBlockTile);
}

void Robot::print() const {
  long maxX{0};
  long maxY{0};

  for (const auto& [point, tile] : _grid) {
    if (point.x > maxX) maxX = point.x;

    if (point.y > maxY) maxY = point.y;
  }

  for (long y = 0; y <= maxY; y++) {
    for (long x = 0; x <= maxX; x++) {
      if (_grid.count(Point{x, y})) {
        switch (_grid.at(Point{x, y})) {
          case TileId::EMPTY:
            std::cout << " ";
            break;
          case TileId::WALL:
            std::cout << "#";
            break;
          case TileId::BLOCK:
            std::cout << "X";
            break;
          case TileId::PADDLE:
            std::cout << "-";
            break;
          case TileId::BALL:
            std::cout << "o";
            break;
        }
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

long Robot::getScore() const { return _score; }

long Robot::getInput() {
  auto isBall = [](const auto& p) { return p.second == TileId::BALL; };

  auto isPaddle = [](const auto& p) { return p.second == TileId::PADDLE; };

  auto ballIt = std::find_if(_grid.begin(), _grid.end(), isBall);
  auto paddleIt = std::find_if(_grid.begin(), _grid.end(), isPaddle);

  if (ballIt->first.x > paddleIt->first.x)
    return 1;
  else if (ballIt->first.x < paddleIt->first.x)
    return -1;
  else
    return 0;
}
