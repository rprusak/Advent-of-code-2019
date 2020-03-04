#include "util.h"
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<std::string> util::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string number;
    while(std::getline(ss, number, delim)) {
        elems.push_back(number);
    }
    return elems;
}

std::vector<std::string> util::readInput(const char* filename) {
    std::ifstream input{filename};

    if (!input.is_open()) {
        std::cerr << "could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> result;
    std::string line;

    while (std::getline(input, line)) {
        result.push_back(line);
    }

    return result;
}