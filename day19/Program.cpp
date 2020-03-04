#include "Program.h"
#include <iostream>
#include <algorithm>

#include "util.h"

Program::Program(const std::string &inputProgram):
        _output{0},
        _programPointer{0},
        _relativeBase{0},
        _isHalted{false},
        _program{convertProgramToInts(inputProgram)} {}

std::vector<long> Program::convertProgramToInts(const std::string &inputProgram) {
    auto values = util::split(inputProgram, ',');
    std::vector<long> result(values.size());

    auto strToInt = [](const std::string& str) {
        return std::stol(str);
    };
    std::transform(values.begin(), values.end(), result.begin(), strToInt);

    return result;
}

long Program::run(long x, long y) {
    bool outputFound{false};
    bool xUsed{false};

    while (_programPointer < _program.size()) {
        if (outputFound)
            break;

        auto instruction = intToInstruction(_program[_programPointer]);
        if (instruction.operationCode == OperationCode::HALT) {
            std::cerr << "HALT" << std::endl;
            _isHalted = true;
            break;
        }

        switch (instruction.operationCode) {
            case OperationCode::ADD:
                handleADD(instruction);
                break;
            case OperationCode::MULTIPLY:
                handleMULTIPLY(instruction);
                break;
            case OperationCode::INPUT:
                {
                    long inputValue{0};
                    if (!xUsed) {
                        inputValue = x;
                        xUsed = true;
                    } else {
                        inputValue = y;
                    }

                    handleINPUT(instruction, inputValue);
                }
                break;
            case OperationCode::OUTPUT:
                handleOUTPUT(instruction);
                outputFound = true;
                break;
            case OperationCode::JUMP_IF_TRUE:
                handleJUMP_IF_TRUE(instruction);
                break;
            case OperationCode::JUMP_IF_FALSE:
                handleJUMP_IF_FALSE(instruction);
                break;
            case OperationCode::LESS_THAN:
                handleLESS_THAN(instruction);
                break;
            case OperationCode::EQUALS:
                handleEQUALS(instruction);
                break;
            case OperationCode::ADJUST_BASE:
                handleADJUST_BASE(instruction);
                break;
            case OperationCode::HALT:
                break;
        }
    }

    return _output;
}

Program::Instruction Program::intToInstruction(long value) {
    Instruction result{};

    result.operationCode = readOperationCode(value);
    result.firstArgumentMode = readParameterMode(value, 1);
    result.secondArgumentMode = readParameterMode(value, 2);
    result.thirdArgumentMode = readParameterMode(value, 3);

    return result;
}

Program::OperationCode Program::readOperationCode(long value) {
    OperationCode code{};

    switch (value % 100) {
        case 1 :
            code = OperationCode::ADD;
            break;
        case 2:
            code = OperationCode::MULTIPLY;
            break;
        case 3:
            code = OperationCode::INPUT;
            break;
        case 4:
            code = OperationCode::OUTPUT;
            break;
        case 5:
            code = OperationCode::JUMP_IF_TRUE;
            break;
        case 6:
            code = OperationCode::JUMP_IF_FALSE;
            break;
        case 7:
            code = OperationCode::LESS_THAN;
            break;
        case 8:
            code = OperationCode::EQUALS;
            break;
        case 9:
            code = OperationCode::ADJUST_BASE;
            break;
        case 99:
            code = OperationCode::HALT;
            break;
        default:
            std::cerr << "unknown operation code" << std::endl;
    }

    return code;
}

Program::ParameterMode Program::readParameterMode(long value, long parameterNumber) {
    ParameterMode result{};

    long factor{100};
    for (long i = 1; i < parameterNumber; i++) {
        factor *= 10;
    }

    switch ((value / factor) % 10) {
        case 0:
            result = ParameterMode::POSITION_MODE;
            break;
        case 1:
            result = ParameterMode::IMMEDIATE_MODE;
            break;
        case 2:
            result = ParameterMode::RELATIVE_MODE;
            break;
        default:
            std::cerr << "unknown parameter mode" << std::endl;
    }

    return result;
}

void Program::handleADD(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);
    long address = readArgumentAsAddress(instruction.thirdArgumentMode, 3);

    _program[address] = firstArgument + secondArgument;
    _programPointer += 4;
}

void Program::handleMULTIPLY(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);
    long address = readArgumentAsAddress(instruction.thirdArgumentMode, 3);

    _program[address] = firstArgument * secondArgument;
    _programPointer += 4;
}

void Program::handleINPUT(Instruction instruction, long input) {
//    std::cout << "[INPUT] " << input << std::endl;
    long firstArgument = readArgumentAsAddress(instruction.firstArgumentMode, 1);
    _program[firstArgument] = input;
    _programPointer += 2;
}

void Program::handleOUTPUT(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);

//    std::cout << "[OUTPUT] " << firstArgument << std::endl;

    _output = firstArgument;
    _programPointer += 2;
}

void Program::handleJUMP_IF_TRUE(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);

    if (firstArgument != 0)
        _programPointer = secondArgument;
    else
        _programPointer += 3;
}

void Program::handleJUMP_IF_FALSE(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);

    if (firstArgument == 0)
        _programPointer = secondArgument;
    else
        _programPointer += 3;
}

void Program::handleLESS_THAN(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);
    long address = readArgumentAsAddress(instruction.thirdArgumentMode, 3);

    if (firstArgument < secondArgument)
        _program[address] = 1;
    else
        _program[address] = 0;

    _programPointer += 4;
}

void Program::handleEQUALS(Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);
    long secondArgument = readArgument(instruction.secondArgumentMode, 2);
    long address = readArgumentAsAddress(instruction.thirdArgumentMode, 3);

    if (firstArgument == secondArgument)
        _program[address] = 1;
    else
        _program[address] = 0;

    _programPointer += 4;
}

void Program::handleADJUST_BASE(Program::Instruction instruction) {
    long firstArgument = readArgument(instruction.firstArgumentMode, 1);

    _relativeBase += firstArgument;
    _programPointer += 2;
}

long Program::readArgument(Program::ParameterMode mode, size_t position) {
    long argument{0};

    switch (mode) {
        case ParameterMode::POSITION_MODE:
            argument = _program[_program[_programPointer + position]];
            break;
        case ParameterMode::IMMEDIATE_MODE:
            argument = _program[_programPointer + position];
            break;
        case ParameterMode::RELATIVE_MODE:
            argument = _program[_relativeBase + _program[_programPointer + position]];
            break;
    }

    return argument;
}

long Program::readArgumentAsAddress(Program::ParameterMode mode, size_t position) {
    long address{0};

    switch (mode) {
        case ParameterMode::POSITION_MODE:
            address = _program[_programPointer + position];
            break;
        case ParameterMode::IMMEDIATE_MODE:
            address = 0;
            std::cerr << "could not read address in immediate mode" << std::endl;
            break;
        case ParameterMode::RELATIVE_MODE:
            address = _relativeBase + _program[_programPointer + position];
            break;
    }

    return address;
}