#include <iostream>
#include <algorithm>
#include "Program.h"

int runAmplifiers(const std::string& inputProgram, const std::vector<int>& phases) {
    std::vector<Program> amplifierPrograms;
    int secondInput{0};

    amplifierPrograms.reserve(5);
    for (int i = 0; i < 5; i++)
        amplifierPrograms.emplace_back(inputProgram);

    auto phaseIt = phases.begin();
    for (auto& program: amplifierPrograms) {
        secondInput = program.run({*phaseIt, secondInput});
        phaseIt++;
    }

    return secondInput;
}

int runAmplifiersWithLoopback(const std::string& inputProgram, const std::vector<int>& phases) {
    std::vector<Program> amplifierPrograms;
    int input{0};

    amplifierPrograms.reserve(5);
    for (int i = 0; i < 5; i++)
        amplifierPrograms.emplace_back(inputProgram);

    auto phaseIt = phases.begin();
    for (auto& program: amplifierPrograms) {
        input = program.run({*phaseIt, input});
        phaseIt++;
    }

    while (!amplifierPrograms.back().isHalted()) {
        for (auto& program: amplifierPrograms) {
            input = program.run({input});
        }
    }
    
    return input;
}

int main() {
    std::string inputProgram{"3,8,1001,8,10,8,105,1,0,0,21,38,59,84,97,110,191,272,353,434,99999,3,9,1002,9,2,9,101,"
                             "4,9,9,1002,9,2,9,4,9,99,3,9,102,5,9,9,1001,9,3,9,1002,9,5,9,101,5,9,9,4,9,99,3,9,102,5,9,"
                             "9,101,5,9,9,1002,9,3,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,101,3,9,9,1002,9,3,9,4,9,99,3,9,"
                             "102,5,9,9,1001,9,3,9,4,9,99,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,"
                             "1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,"
                             "3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,"
                             "2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,"
                             "9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,"
                             "3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,"
                             "4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,101,2,9,9,4,9,3,9,101,"
                             "1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,"
                             "2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,"
                             "3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,"
                             "9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,99"};

    {
        std::vector<int> phases{0, 1, 2, 3, 4};

        auto bestResult = runAmplifiers(inputProgram, phases);

        do {
            auto result = runAmplifiers(inputProgram, phases);
            if (result > bestResult)
                bestResult = result;
        } while(std::next_permutation(phases.begin(), phases.end()));

        std::cout << bestResult << std::endl;
    }

    {
        std::vector<int> phases{5, 6, 7, 8, 9};

        auto bestResult = runAmplifiersWithLoopback(inputProgram, phases);

        do {
            auto result = runAmplifiersWithLoopback(inputProgram, phases);
            if (result > bestResult)
                bestResult = result;
        } while(std::next_permutation(phases.begin(), phases.end()));

        std::cout << bestResult << std::endl;
    }

    return 0;
}
