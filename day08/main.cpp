#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>

std::string readInput(const char* filename) {
  std::ifstream input{filename};
  if (!input.is_open()) {
    std::cerr << "could not open file " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string result;
  input >> result;

  return result;
}

unsigned findPixel(const std::string& input, size_t widthIndex,
                   size_t heightIndex) {
  for (unsigned layer = 0; layer < 100; layer++) {
    auto layerBegin = input.begin() + layer * (25 * 6);
    auto pixelIt = layerBegin + widthIndex * 25 + heightIndex;
    if (*pixelIt != '2') return *pixelIt - 48;
  }

  return 2;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "invalid input" << std::endl;
  }

  constexpr unsigned width{25};
  constexpr unsigned height{6};

  auto input = readInput(argv[1]);

  unsigned fewestZerosCount{1000};
  unsigned result{0};

  for (size_t i = 0; i < input.size(); i += width * height) {
    auto zerosCount = std::count(input.begin() + i,
                                 input.begin() + i + (width * height), '0');
    if (zerosCount < fewestZerosCount) {
      fewestZerosCount = zerosCount;
      auto oneCount = std::count(input.begin() + i,
                                 input.begin() + i + (width * height), '1');
      auto twoCount = std::count(input.begin() + i,
                                 input.begin() + i + (width * height), '2');
      result = oneCount * twoCount;
    }
  }

  std::cout << result << std::endl;

  std::cout << "============================================" << std::endl;

  unsigned layersCount = input.size() / (height * width);

  std::array<std::array<unsigned, 25>, 6> outputImage{};

  for (size_t row = 0; row < outputImage.size(); row++) {
    for (size_t column = 0; column < outputImage[row].size(); column++) {
      outputImage[row][column] = findPixel(input, row, column);
    }
  }

  for (size_t w = 0; w < outputImage.size(); w++) {
    for (size_t h = 0; h < outputImage[w].size(); h++) {
      std::cout << outputImage[w][h] << ' ';
    }

    std::cout << std::endl;
  }

  return 0;
}
