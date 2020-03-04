#ifndef DAY11_ROBOT_H
#define DAY11_ROBOT_H

#include <utility>
#include <map>
#include "RobotInterface.h"

class Robot: public RobotInterface {
public:
    long getCurrentColor() override;

    void colorCurrentPanel(long color) override;

    void move(long direction) override;

    long panelsCount() const;
    void setStartColor(long color);
    void print();

private:
    struct Point {
        long x{0};
        long y{0};

        bool operator< (const Point& p) const {
            if (this->x < p.x)
                return true;
            else if (p.x < this->x)
                return false;
            else
                return this->y < p.y;
        }
    };

    struct Panel {
        long color{0};
        long paintCounter{0};
    };

    enum class Direction {
        UP,
        LEFT,
        DOWN,
        RIGHT
    };

    Point _currentPoint{0, 0};
    std::map<Point, Panel> _paintedPanels;
    Direction _currentDirection{Direction::UP};
    bool _startColorUsed{false};
    long _startColor{0};

    void changeDirection(long turnDirection);
    void move();
};


#endif //DAY11_ROBOT_H
