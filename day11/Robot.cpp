#include "Robot.h"
#include <iostream>

long Robot::getCurrentColor() {
    if (!_paintedPanels.count(_currentPoint)) {
        if (_startColorUsed)
            return 0;

        _startColorUsed = true;
        return _startColor;
    }
    else
        return _paintedPanels.at(_currentPoint).color;
}

void Robot::colorCurrentPanel(long color) {
    if (color != 0 && color != 1) {
        std::cerr << "invalid color" << std::endl;
        return;
    }

    if (!_paintedPanels.count(_currentPoint)) {
        _paintedPanels.emplace(std::make_pair(_currentPoint, Panel{color, 1}));
    } else {
        _paintedPanels[_currentPoint].color = color;
        _paintedPanels[_currentPoint].paintCounter += 1;
    }
}

void Robot::move(long direction) {
    if (direction != 0 && direction != 1) {
        std::cerr << "invalid direction" << std::endl;
        return;
    }

    changeDirection(direction);
    move();
}

void Robot::changeDirection(long turnDirection) {
    switch (_currentDirection) {
        case Direction::UP:
            _currentDirection = turnDirection ? Direction::RIGHT : Direction::LEFT;
            break;
        case Direction::LEFT:
            _currentDirection = turnDirection ? Direction::UP : Direction::DOWN;
            break;
        case Direction::DOWN:
            _currentDirection = turnDirection ? Direction::LEFT : Direction::RIGHT;
            break;
        case Direction::RIGHT:
            _currentDirection = turnDirection ? Direction::DOWN : Direction::UP;
            break;
    }
}

void Robot::move() {
    switch (_currentDirection) {
        case Direction::UP:
            _currentPoint.y += 1;
            break;
        case Direction::LEFT:
            _currentPoint.x -= 1;
            break;
        case Direction::DOWN:
            _currentPoint.y -= 1;
            break;
        case Direction::RIGHT:
            _currentPoint.x += 1;
            break;
    }
}

long Robot::panelsCount() const {
    return _paintedPanels.size();
}

void Robot::setStartColor(long color) {
    _startColor = color;

}

void Robot::print() {
    long minX = {0};
    long maxX = {0};
    long maxY = {0};
    long minY = {0};

    for(const auto& [point, panel] : _paintedPanels) {
        if (point.x > maxX)
            maxX = point.x;

        if (point.y > maxY)
            maxY = point.y;

        if (point.x < minX)
            minX = point.x;

        if (point.y < minY)
            minY = point.y;
    }

    for (long y = maxY; y >= minY; y--) {
        for (long x = minX; x <= maxX; x++) {
            Point p {x,y};

            if (!_paintedPanels.count(p))
                std::cout << " ";
            else if (_paintedPanels[p].color)
                std::cout << "#";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}




