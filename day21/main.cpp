#include <iostream>
#include "util.h"
#include "Program.h"
#include "ProgramInput.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "invalid program arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto intcodeProgram = util::readInput(argv[1]).front();

    ProgramInput programInput;
    Program p{intcodeProgram, programInput};

    while (!p.isHalted())
        p.run();

    std::cout << std::endl << p.getOutput() << std::endl;
    return 0;
}
