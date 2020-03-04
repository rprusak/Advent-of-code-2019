#include <iostream>
#include <string>

#include "Droid.h"
#include "Program.h"
#include "util.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid input" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto inputProgram = util::readInput(argv[1]).front();
  Program program{inputProgram};

  Droid droid{program};
  droid.run();

  std::cout << droid.fillWithOxygen() << std::endl;

  return 0;
}
