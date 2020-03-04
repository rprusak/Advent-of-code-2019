#include "Droid.h"
#include <iostream>
#include <vector>
#include <algorithm>

#include "dijkstra.h"

Droid::Droid(ProgramInterface &program) :
    _program(program),
    _dev{},
    _rng{_dev()} {
    _area[_currentPosition] = FieldType::EMPTY;
    _visitedStatus[_currentPosition] = true;
}

void Droid::run() {
    bool oxygenFound{false};

    while (!oxygenFound) {
        _visitedStatus[_currentPosition] = true;

        if (hasNotDiscoveredFieldsAround()) {
            auto notDiscoveredFields = getNotDiscoveredFieldsAround();

            for (const auto& field : notDiscoveredFields) {
                auto output = _program.run(field.second);
                auto fieldType = getFieldType(output);
                _area[field.first] = fieldType;

                switch (fieldType) {
                    case FieldType::EMPTY:
                        _visitedStatus[field.first] = false;
                        _program.run(getOppositeDirection(field.second));
                        break;
                    case FieldType::WALL:
                        _visitedStatus[field.first] = true;
                        break;
                    case FieldType::OXYGEN:
                        _visitedStatus[field.first] = true;
                        _oxygenPoint = field.first;
                        oxygenFound = true;
                        _program.run(getOppositeDirection(field.second));
                        break;
                }
            }
        } else {
            auto direction = getMoveDirection();
            auto programOutput = _program.run(direction.second);
            auto fieldType = getFieldType(programOutput);


            switch (fieldType) {
                case FieldType::EMPTY:
                    _currentPosition = direction.first;
                    _area[_currentPosition] = fieldType;
                    break;
                case FieldType::WALL:
                    _visitedStatus[direction.first] = true;
                    _area[direction.first] = fieldType;
                    break;
                case FieldType::OXYGEN:
                    _visitedStatus[direction.first] = true;
                    _area[direction.first] = fieldType;
                    _oxygenPoint = direction.first;
                    oxygenFound = true;
                    break;
            }
        }
    }

//    std::cout << "unvisited count " << _visitedStatus.unvisitedCount() << std::endl;
//    print();

    while(_visitedStatus.hasUnvisited()) {
        _visitedStatus[_currentPosition] = true;

        if (hasNotDiscoveredFieldsAround()) {
            auto notDiscoveredFields = getNotDiscoveredFieldsAround();

            for (const auto& field : notDiscoveredFields) {
                auto output = _program.run(field.second);
                auto fieldType = getFieldType(output);
                _area[field.first] = fieldType;

                switch (fieldType) {
                    case FieldType::EMPTY:
                        _visitedStatus[field.first] = false;
                        _program.run(getOppositeDirection(field.second));
                        break;
                    case FieldType::WALL:
                        _visitedStatus[field.first] = true;
                        break;
                    case FieldType::OXYGEN:
                        _visitedStatus[field.first] = true;
                        _program.run(getOppositeDirection(field.second));
                        break;
                }
            }
        } else {
            auto direction = getMoveDirection();
            auto programOutput = _program.run(direction.second);
            auto fieldType = getFieldType(programOutput);

            switch (fieldType) {
                case FieldType::EMPTY:
                    _currentPosition = direction.first;
                    _area[_currentPosition] = fieldType;
                    break;
                case FieldType::WALL:
                    _visitedStatus[direction.first] = true;
                    _area[direction.first] = fieldType;
                    break;
                case FieldType::OXYGEN:
                    _visitedStatus[direction.first] = true;
                    _area[direction.first] = fieldType;
                    break;
            }
        }

    }
//    std::cout << "unvisited count " << _visitedStatus.size() << std::endl;
}

bool Droid::hasNotDiscoveredFieldsAround() const {
    auto directions = getDirections();

    auto isNotDiscovered = [this](const Direction& direction) {
        return this->_area.count(direction.first) == 0;
    };

    return std::find_if(directions.begin(), directions.end(), isNotDiscovered) != directions.end();
}

std::vector<Droid::Direction> Droid::getDirections() const {
    std::vector<Direction> directions{
            {Point{_currentPosition.x, _currentPosition.y + 1}, 1}, // NORTH
            {Point{_currentPosition.x, _currentPosition.y - 1}, 2}, // SOUTH
            {Point{_currentPosition.x - 1, _currentPosition.y}, 3}, // WEST
            {Point{_currentPosition.x + 1, _currentPosition.y}, 4}  // EAST
    };

    return directions;
}

std::vector<Droid::Direction> Droid::getNotDiscoveredFieldsAround() const {
    auto directions = getDirections();
    std::vector<Droid::Direction> result;

    auto isNotDiscovered = [this](const Direction& direction) {
        return this->_area.count(direction.first) == 0;
    };

    std::copy_if(directions.begin(), directions.end(), std::back_inserter(result), isNotDiscovered);
    return result;
}

Droid::Direction Droid::getMoveDirection() {
    std::vector<Direction> possibleDirections = getDirections();

    auto isEmptyField = [this](const Direction& direction) {
        return this->_area.at(direction.first) == FieldType::EMPTY;
    };

    std::vector<Direction> emptyFields;
    std::copy_if(possibleDirections.begin(), possibleDirections.end(), std::back_inserter(emptyFields), isEmptyField);

    std::uniform_int_distribution<std::mt19937::result_type> dist(0,emptyFields.size() - 1);
    auto index = dist(_rng);

    return emptyFields[index];
}

Droid::FieldType Droid::getFieldType(long value) const {
    switch (value) {
        case 0:
            return FieldType::WALL;
        case 1:
            return FieldType::EMPTY;
        case 2:
            return FieldType::OXYGEN;
        default:
            std::cerr << "invalid field type value" << std::endl;
    }

    return FieldType::WALL;
}

void Droid::print() const {
    long maxX{0};
    long minX{0};
    long maxY{0};
    long minY{0};

    for (const auto& [point, field] : _area) {
        if (point.x > maxX) {
            maxX = point.x;
        }

        if (point.y > maxY) {
            maxY = point.y;
        }

        if (point.y< minY) {
            minY = point.y;
        }

        if (point.x < minX) {
            minX = point.x;
        }
    }

    std::cout << std::endl;

    for (long y = maxY; y >= minY; y--) {
        for (long x = minX; x <= maxX; x++) {
            Point p{x, y};

            if (x == _currentPosition.x && y == _currentPosition.y) {
                std::cout << "D";
            } else {

                if (!_area.count(p)) {
                    std::cout << " ";
                } else {
                    if (_visitedStatus.count(p) && !_visitedStatus.at(p)) {
                        std::cout << "X";
                    } else {
                        auto field = _area.at(p);
                        switch (field) {
                            case FieldType::EMPTY:
                                std::cout << "*";
                                break;
                            case FieldType::WALL:
                                std::cout << "#";
                                break;
                            case FieldType::OXYGEN:
                                std::cout << "O";
                                break;
                        }
                    }
                }
            }

        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

long Droid::getOppositeDirection(long direction) const {
    switch (direction) {
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 4;
        case 4:
            return 3;
        default:
            std::cerr << "invalid direction" << std::endl;
    }
}

long Droid::getShortestPathLength() {
    std::vector<Point> points;
    for (const auto& [point, field] : _area) {
        if (field != FieldType::WALL)
            points.push_back(point);
    }

    std::vector<std::vector<int>> graph{points.size()};
    for (auto& record : graph)
        record.resize(points.size(), 0);

    for (const auto& point : points) {
        _currentPosition = point;
        auto pointIndex = std::distance(points.begin(), std::find(points.begin(), points.end(), point));
        auto movableFields = getMovableFieldsAround();
        for (const auto& [secondPoint, field] : movableFields) {
            auto secondPointIndex = std::distance(points.begin(), std::find(points.begin(), points.end(), secondPoint));
            graph[pointIndex][secondPointIndex] = 1;
            graph[secondPointIndex][pointIndex] = 1;
        }
    }

    auto startIndex = std::distance(points.begin(), std::find(points.begin(), points.end(), Point{0, 0}));
    auto destinationIndex = std::distance(points.begin(), std::find(points.begin(), points.end(), Point{-16, -12}));

    return dijkstra(graph, startIndex, destinationIndex);
}

std::vector<Droid::Direction> Droid::getMovableFieldsAround() const {
    auto directions = getDirections();

    auto isMovableField = [this](const Direction& direction) {
        return this->_area.count(direction.first) && this->_area.at(direction.first) != FieldType::WALL;
    };

    std::vector<Direction> movableFields;
    std::copy_if(directions.begin(), directions.end(), std::back_inserter(movableFields), isMovableField);

    return movableFields;
}

long Droid::fillWithOxygen() {
    long requiredTime{0};

    while (!isFullyFilled()) {
        requiredTime++;
        auto oxygenPoints = getOxygenPoints();
        for (const auto& oxygenPoint : oxygenPoints) {
            _currentPosition = oxygenPoint;
            auto fields = getEmptyFieldsAround();
            for (const auto& field : fields) {
                _area.at(field) = FieldType::OXYGEN;
            }
        }
    }

    return requiredTime;
}

bool Droid::isFullyFilled() const {
    auto isEmptyField = [this](const auto& field) {
        return field.second == FieldType::EMPTY;
    };

    return !std::any_of(_area.begin(), _area.end(), isEmptyField);
}

std::vector<Droid::Point> Droid::getOxygenPoints() const {
    std::vector<Droid::Point> oxygenPoints;
    for (const auto& field : _area) {
        if (field.second == FieldType::OXYGEN) {
            oxygenPoints.push_back(field.first);
        }
    }

    return oxygenPoints;
}

std::vector<Droid::Point> Droid::getEmptyFieldsAround() const {
    auto directions = getDirections();
    std::vector<Droid::Point> emptyPoints;

    auto isEmptyField = [this](const Direction& direction) {
        return this->_area.count(direction.first) && this->_area.at(direction.first) == FieldType::EMPTY;
    };

    for (const auto& direction : directions) {
        if (isEmptyField(direction))
            emptyPoints.push_back(direction.first);
    }

    return emptyPoints;
}
