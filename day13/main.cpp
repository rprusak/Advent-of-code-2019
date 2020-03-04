#include <iostream>
#include <string>
#include "util.h"
#include "Program.h"
#include "Robot.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto inputProgram = util::readInput(argv[1]).front();

    Robot robot;

    Program program{inputProgram, robot};
    program.run();

    std::cout << robot.getBlockTilesCount() << std::endl;

    std::cout << std::endl;
    robot.print();

    Program program2{inputProgram, robot};
    program2.setCoin(2);
    program2.run();

    std::cout << robot.getScore() << std::endl;

    return 0;
}
