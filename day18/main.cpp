#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#include "util.h"

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

class Vault: public std::map<Point, char> {
public:
    Point getStartingPoint() {
        auto isStartingPoint = [](const auto& val) {
            return val.second == '@';
        };

        auto it = std::find_if(begin(), end(), isStartingPoint);

        if (it == end()) {
            std::cerr << "could not find starting point" << std::endl;
            exit(EXIT_FAILURE);
        }

        it->second = '.';
        return it->first;
    }

    bool isFullyVisited() const {
        auto isVisited = [](const auto& val) {
            return val.second == '.';
        };

        return std::all_of(begin(), end(), isVisited);
    }

    std::vector<Point> getAvailableKeys(const Point& startingPosition) const {
        std::queue<Point> pointsToCheck;
        std::set<Point> visitedPoints;
        std::vector<Point> keys;
        pointsToCheck.push(startingPosition);

        while (!pointsToCheck.empty()) {
            auto point =  pointsToCheck.front();
            pointsToCheck.pop();

            visitedPoints.insert(point);


        }

        return keys;
    }

private:
    std::vector<Point> getNearPoints(const Point& p) const {
        std::vector<Point> nearPoints {
            Point{p._x - 1, p._y},
            Point{p._x + 1, p._y},
            Point{p._x, p._y - 1},
            Point{p._x, p._y + 1}
        };

        auto pointNotExists = [this](const Point& p) {
            return count(p) == 0;
        };

        auto it = std::remove_if(nearPoints.begin(), nearPoints.end(), pointNotExists);
        nearPoints.erase(it, nearPoints.end());

        return nearPoints;
    }

    static bool isKey(char c) {
        return islower(c);
    }

    static bool isDoor(char c) {
        return isupper(c);
    }
};

Vault parseInput(const std::vector<std::string>& programInput) {
    Vault vault;

    for (size_t y = 0; y < programInput.size(); y++) {
        for (size_t x = 0; x < programInput.front().size(); x++) {
            if (programInput[y][x] != '#') {
                vault[Point{x, y}] = programInput[y][x];
            }
        }
    }

    return vault;
}

unsigned long visit(Vault& vault) {
    unsigned long pathLength{0};

    auto currentPosition = vault.getStartingPoint();

    while (!vault.isFullyVisited()) {

        break;
    }


    return pathLength;
}

unsigned long getPathLength(const std::string& filename) {
    auto programInput = util::readInput(filename.c_str());
    auto vault = parseInput(programInput);
    return visit(vault);
}

int main() {
    std::string input1{"/home/rafal/Workspace/advent_of_code_2019/day18/input1.txt"};

    std::cout << std::boolalpha << (getPathLength(input1) == 8) << std::endl;

    return 0;
}
