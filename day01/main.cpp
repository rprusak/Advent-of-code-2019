#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

unsigned getFuel(unsigned mass) {
    return unsigned(mass / 3) - 2;
}

unsigned getFuel2(unsigned mass) {
    auto fuel = unsigned(mass / 3) - 2;
    if (fuel <= 5 )
        return fuel;
    else
        return fuel + getFuel2(fuel);
}

std::vector<unsigned> readInput(const char* filename) {
    std::ifstream input{filename};
    std::vector<unsigned> result;
    unsigned value;

    while (input) {
        if (input >> value)
            result.push_back(value);
        else
            break;
    }

    return result;
}

void partOne(const std::vector<unsigned>& input) {
    unsigned result{0};

    for (auto mass : input) {
        result += getFuel(mass);
    }

    std::cout << result << std::endl;
}

void partTwo(const std::vector<unsigned>& input) {
    unsigned result{0};

    for (auto mass : input) {
        result += getFuel2(mass);
    }

    std::cout << result << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "invalid arguments" << std::endl;
        return 1;
    }

    auto input = readInput(argv[1]);

    partOne(input);
    partTwo(input);

    return 0;
}
