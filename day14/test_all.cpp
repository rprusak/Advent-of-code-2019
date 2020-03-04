#include <iostream>
#include "FuelCalculator.h"

void part1() {
    std::string p1{"/home/rafal/Workspace/advent_of_code_2019/day14/input.txt"};
    std::string p2{"/home/rafal/Workspace/advent_of_code_2019/day14/input2.txt"};
    std::string p3{"/home/rafal/Workspace/advent_of_code_2019/day14/input3.txt"};
    std::string p4{"/home/rafal/Workspace/advent_of_code_2019/day14/input4.txt"};
    std::string p5{"/home/rafal/Workspace/advent_of_code_2019/day14/input5.txt"};
    std::string p6{"/home/rafal/Workspace/advent_of_code_2019/day14/main_input.txt"};

    std::cout << std::boolalpha << (FuelCalculator{p1}.calculateOrePerFuel() == 31) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p2}.calculateOrePerFuel() == 165) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p3}.calculateOrePerFuel() == 13312) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p4}.calculateOrePerFuel() == 180697) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p5}.calculateOrePerFuel() == 2210736) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p6}.calculateOrePerFuel() == 612880) << std::endl;
}

void part2() {
    unsigned long ores{1000000000000};

    std::string p3{"/home/rafal/Workspace/advent_of_code_2019/day14/input3.txt"};
    std::string p4{"/home/rafal/Workspace/advent_of_code_2019/day14/input4.txt"};
    std::string p5{"/home/rafal/Workspace/advent_of_code_2019/day14/input5.txt"};
    std::string p6{"/home/rafal/Workspace/advent_of_code_2019/day14/main_input.txt"};

    std::cout << std::boolalpha << (FuelCalculator{p4}.calculateFuelCount(ores) == 5586022UL) << std::endl;
    std::cout << std::boolalpha << (FuelCalculator{p5}.calculateFuelCount(ores) == 460664UL) << std::endl;
}


int main() {
    part2();


    return 0;
}