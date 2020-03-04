#include <iostream>
#include <vector>
#include <algorithm>
#include "util.h"

enum class OperationCode {
    ADD,
    MULTIPLY,
    INPUT,
    OUTPUT,
    JUMP_IF_TRUE,
    JUMP_IF_FALSE,
    LESS_THAN,
    EQUALS,
    HALT
};

enum class ParameterMode {
    POSITION_MODE,
    IMMEDIATE_MODE
};

struct Instruction {
    OperationCode operationCode;
    ParameterMode firstArgumentMode;
    ParameterMode secondArgumentMode;
    ParameterMode thirdArgumentMode;
};

OperationCode readOperationCode(int value) {
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
        case 99:
            code = OperationCode::HALT;
            break;
        default:
            std::cerr << "unknown operation code" << std::endl;
    }

    return code;
}

ParameterMode readParameterMode(int value, int parameterNumber) {
    ParameterMode result{};

    int factor{100};
    for (int i = 1; i < parameterNumber; i++) {
        factor *= 10;
    }

    switch ((value / factor) % 10) {
        case 0:
            result = ParameterMode::POSITION_MODE;
            break;
        case 1:
            result = ParameterMode::IMMEDIATE_MODE;
            break;
        default:
            std::cerr << "unknown parameter mode" << std::endl;
    }

    return result;
}

Instruction intToInstruction(int value) {
    Instruction result{};

    result.operationCode = readOperationCode(value);
    result.firstArgumentMode = readParameterMode(value, 1);
    result.secondArgumentMode = readParameterMode(value, 2);
    result.thirdArgumentMode = readParameterMode(value, 3);

    return result;
}

std::vector<int> convertProgramToInts(const std::string& inputProgram) {
    auto values = util::split(inputProgram, ',');
    std::vector<int> result(values.size());

    auto strToInt = [](const std::string& str) {
        return std::stoi(str);
    };
    std::transform(values.begin(), values.end(), result.begin(), strToInt);

    return result;
}

void handleADD(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    program[program[programPointer + 3]] = firstArgument + secondArgument;
    programPointer += 4;
}

void handleMULTIPLY(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    program[program[programPointer + 3]] = firstArgument * secondArgument;
    programPointer += 4;
}

void handleINPUT(int input, std::vector<int>& program, size_t& programPointer) {
    program[program[programPointer + 1]] = input;
    programPointer += 2;

}

void handleOUTPUT(std::vector<int>& program, size_t& programPointer) {
    std::cout << "[OUTPUT] " << program[program[programPointer + 1]] << std::endl;
    programPointer += 2;
}

void handleJUMP_IF_TRUE(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    if (firstArgument != 0)
        programPointer = secondArgument;
    else
        programPointer += 3;
}

void handleJUMP_IF_FALSE(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    if (firstArgument == 0)
        programPointer = secondArgument;
    else
        programPointer += 3;
}

void handleLESS_THAN(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    if (firstArgument < secondArgument)
        program[program[programPointer + 3]] = 1;
    else
        program[program[programPointer + 3]] = 0;

    programPointer += 4;
}

void handleEQUALS(Instruction instruction, std::vector<int>& program, size_t& programPointer) {
    int firstArgument{0};
    int secondArgument{0};

    if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        firstArgument = program[programPointer + 1];
    } else {
        firstArgument = program[program[programPointer + 1]];
    }

    if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
        secondArgument = program[programPointer + 2];
    } else {
        secondArgument = program[program[programPointer + 2]];
    }

    if (firstArgument == secondArgument)
        program[program[programPointer + 3]] = 1;
    else
        program[program[programPointer + 3]] = 0;

    programPointer += 4;
}

void runProgram(std::vector<int>& inputProgram, int inputValue) {
    size_t programPointer{0};

    while (programPointer < inputProgram.size()) {
        auto instruction = intToInstruction(inputProgram[programPointer]);
        if (instruction.operationCode == OperationCode::HALT)
            break;

        switch (instruction.operationCode) {
            case OperationCode::ADD:
                handleADD(instruction, inputProgram, programPointer);
                break;
            case OperationCode::MULTIPLY:
                handleMULTIPLY(instruction, inputProgram, programPointer);
                break;
            case OperationCode::INPUT:
                handleINPUT(inputValue, inputProgram, programPointer);
                break;
            case OperationCode::OUTPUT:
                handleOUTPUT(inputProgram, programPointer);
                break;
            case OperationCode::JUMP_IF_TRUE:
                handleJUMP_IF_TRUE(instruction, inputProgram, programPointer);
                break;
            case OperationCode::JUMP_IF_FALSE:
                handleJUMP_IF_FALSE(instruction, inputProgram, programPointer);
                break;
            case OperationCode::LESS_THAN:
                handleLESS_THAN(instruction, inputProgram, programPointer);
                break;
            case OperationCode::EQUALS:
                handleEQUALS(instruction, inputProgram, programPointer);
                break;
            case OperationCode::HALT:
                break;
        }
    }
}

int main() {
    std::string inputProgram{"3,225,1,225,6,6,1100,1,238,225,104,0,1002,43,69,224,101,-483,224,224,4,224,1002,223,8,223,1001,224,5,224,1,224,223,223,1101,67,60,225,1102,5,59,225,1101,7,16,225,1102,49,72,225,101,93,39,224,101,-98,224,224,4,224,102,8,223,223,1001,224,6,224,1,224,223,223,1102,35,82,225,2,166,36,224,101,-4260,224,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,102,66,48,224,1001,224,-4752,224,4,224,102,8,223,223,1001,224,2,224,1,223,224,223,1001,73,20,224,1001,224,-55,224,4,224,102,8,223,223,101,7,224,224,1,223,224,223,1102,18,41,224,1001,224,-738,224,4,224,102,8,223,223,101,6,224,224,1,224,223,223,1101,68,71,225,1102,5,66,225,1101,27,5,225,1101,54,63,224,1001,224,-117,224,4,224,102,8,223,223,1001,224,2,224,1,223,224,223,1,170,174,224,101,-71,224,224,4,224,1002,223,8,223,1001,224,4,224,1,223,224,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1007,226,226,224,1002,223,2,223,1006,224,329,1001,223,1,223,1007,226,677,224,102,2,223,223,1006,224,344,1001,223,1,223,108,677,677,224,102,2,223,223,1005,224,359,1001,223,1,223,1007,677,677,224,1002,223,2,223,1006,224,374,101,1,223,223,8,677,226,224,1002,223,2,223,1006,224,389,101,1,223,223,7,226,226,224,1002,223,2,223,1005,224,404,101,1,223,223,7,677,226,224,102,2,223,223,1005,224,419,1001,223,1,223,8,226,677,224,1002,223,2,223,1005,224,434,101,1,223,223,1008,226,677,224,102,2,223,223,1006,224,449,1001,223,1,223,7,226,677,224,1002,223,2,223,1006,224,464,1001,223,1,223,108,677,226,224,102,2,223,223,1005,224,479,101,1,223,223,108,226,226,224,1002,223,2,223,1006,224,494,101,1,223,223,8,226,226,224,1002,223,2,223,1005,224,509,1001,223,1,223,1107,677,226,224,102,2,223,223,1005,224,524,1001,223,1,223,1107,226,226,224,102,2,223,223,1005,224,539,1001,223,1,223,1108,677,677,224,1002,223,2,223,1006,224,554,101,1,223,223,107,226,677,224,102,2,223,223,1005,224,569,1001,223,1,223,1108,226,677,224,1002,223,2,223,1005,224,584,1001,223,1,223,1107,226,677,224,1002,223,2,223,1005,224,599,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,614,101,1,223,223,107,226,226,224,102,2,223,223,1006,224,629,1001,223,1,223,1008,677,677,224,1002,223,2,223,1006,224,644,101,1,223,223,107,677,677,224,1002,223,2,223,1005,224,659,101,1,223,223,1108,677,226,224,1002,223,2,223,1006,224,674,1001,223,1,223,4,223,99,226"};
    auto input = convertProgramToInts(inputProgram);

//    runProgram(input, 1);
    std::cout << "==========================" << std::endl;
    runProgram(input, 5);

    return 0;
}
