#include <iostream>

#include "FuelCalculator.h"

void part1(const char* path) {
  FuelCalculator fuelCalculator{path};
  std::cout << fuelCalculator.calculateOrePerFuel() << std::endl;
}

void part2(const char* path) {
  unsigned long ores{1000000000000};
  FuelCalculator fuelCalculator{path};
  std::cout << fuelCalculator.calculateFuelCount(ores) << std::endl;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "" << std::endl;
    exit(EXIT_FAILURE);
  }

  part1(argv[1]);
  part2(argv[1]);

  return 0;
}
