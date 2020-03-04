#include "ProgramMemory.h"

ProgramMemory::ProgramMemory(const std::vector<long> &program) : _program(program) {
    _program.resize(10000, 0);
}

long &ProgramMemory::operator[](std::vector<long>::size_type index) {
    if (index < _program.size()) {
        return _program[index];
    } else {
        return _additionalMemory[index];
    }
}
