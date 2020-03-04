#include <optional>
#include <algorithm>
#include <set>
#include <numeric>
#include "day17.h"

struct Point {
    unsigned long _x{0};
    unsigned long _y{0};

    bool operator==(const Point& p) const  {
        return _x == p._x && _y == p._y;
    }

    bool operator<(const Point& p) const {
        if (_x < p._x)
            return true;
        else if (p._x < _x)
            return false;
        else
            return _y < p._y;
    }
};

class Line: public std::vector<Point> {
public:
    std::optional<Point> getIntersectionPoint(const Line& line) const {
        auto hasCommonPoint = [this](const Point& p) {
            return std::find(begin(), end(), p) != end();
        };

        auto it = std::find_if(line.begin(), line.end(), hasCommonPoint);

        if (it == line.end())
            return std::nullopt;

        auto p = *it;

        if (p == front() || p == back())
            return std::nullopt;

        return std::make_optional(*it);
    }
};

std::vector<Line> getHorizontalLines(const std::vector<std::string>& input) {
    std::vector<Line> horizontalLines;

    auto inputHeight{input.size()};
    auto inputWidth{input.front().size()};

    for (size_t y = 0; y < inputHeight; y++) {
        Line line;
        for (size_t x = 0; x < inputWidth; x++) {
            auto c = input[y][x];
            if (c == '#') {
                line.push_back(Point{x, y});
            } else if (!line.empty()) {
                if (line.size() > 1)
                    horizontalLines.push_back(line);
                line.clear();
            }
        }

        if (!line.empty() && line.size() > 1)
            horizontalLines.push_back(line);
    }

    return horizontalLines;
}

std::vector<Line> getVerticalLines(const std::vector<std::string>& input) {
    std::vector<Line> verticalLines;

    auto inputHeight{input.size()};
    auto inputWidth{input.front().size()};

    for (size_t x = 0; x < inputWidth; x++) {
        Line line;
        for (size_t y = 0; y < inputHeight; y++) {
            auto c = input[y][x];
            if (c == '#') {
                line.push_back(Point{x, y});
            } else if (!line.empty()) {
                if (line.size() > 1)
                    verticalLines.push_back(line);
                line.clear();
            }
        }

        if (!line.empty() && line.size() > 1)
            verticalLines.push_back(line);
    }

    return verticalLines;
}

unsigned long getSumOfTheAlignmentParameters(const std::vector<std::string>& input) {
    auto verticalLines = getVerticalLines(input);
    auto horizontalLines = getHorizontalLines(input);

    std::set<Point> intersectionPoints;

    for (const auto& verticalLine : verticalLines) {
        for (const auto& horizontalLine : horizontalLines) {
            auto intersectionPoint = verticalLine.getIntersectionPoint(horizontalLine);

            if (intersectionPoint.has_value())
                intersectionPoints.insert(intersectionPoint.value());
        }
    }

    unsigned long sum{0};
    for (const auto& p : intersectionPoints)
        sum += p._x * p._y;

    return sum;
}