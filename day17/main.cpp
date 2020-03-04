#include <iostream>

#include "Program.h"
#include "day17.h"
#include "util.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invali input" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto input = util::readInput(argv[1]).front();

  Program program{input};

  while (!program.isHalted()) program.run(0);

  auto cameraView = program.getCameraView();
  auto splitCameraView = util::split(cameraView, '\n');

  //    std::vector<std::string> testInput{
  //        "..#..........",
  //        "..#..........",
  //        "#######...###",
  //        "#.#...#...#.#",
  //        "#############",
  //        "..#...#...#..",
  //        "..#####...^.."
  //    };

  std::cout << getSumOfTheAlignmentParameters(splitCameraView) << std::endl;

  return 0;
}
