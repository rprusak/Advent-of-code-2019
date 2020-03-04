#include "Program.h"

#include <algorithm>
#include <iostream>

#include "util.h"

Program::Program(const std::string &inputProgram)
    : _output{0}, _programPointer{0}, _ishalted{false} {
  _program = convertProgramToInts(inputProgram);
}

std::vector<int> Program::convertProgramToInts(
    const std::string &inputProgram) {
  auto values = util::split(inputProgram, ',');
  std::vector<int> result(values.size());

  auto strToInt = [](const std::string &str) { return std::stoi(str); };
  std::transform(values.begin(), values.end(), result.begin(), strToInt);

  return result;
}

int Program::run(const std::vector<int> &inputValues) {
  auto inputIt = inputValues.begin();
  bool outputFound{false};

  while (_programPointer < _program.size() && !outputFound) {
    auto instruction = intToInstruction(_program[_programPointer]);
    if (instruction.operationCode == OperationCode::HALT) {
      _ishalted = true;
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
        handleINPUT(*inputIt);
        inputIt++;
        break;
      case OperationCode::OUTPUT:
        handleOUTPUT();
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
      case OperationCode::HALT:
        break;
    }
  }

  return _output;
}

Program::Instruction Program::intToInstruction(int value) {
  Instruction result{};

  result.operationCode = readOperationCode(value);
  result.firstArgumentMode = readParameterMode(value, 1);
  result.secondArgumentMode = readParameterMode(value, 2);
  result.thirdArgumentMode = readParameterMode(value, 3);

  return result;
}

Program::OperationCode Program::readOperationCode(int value) {
  OperationCode code{};

  switch (value % 100) {
    case 1:
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

Program::ParameterMode Program::readParameterMode(int value,
                                                  int parameterNumber) {
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

void Program::handleADD(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  _program[_program[_programPointer + 3]] = firstArgument + secondArgument;
  _programPointer += 4;
}

void Program::handleMULTIPLY(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  _program[_program[_programPointer + 3]] = firstArgument * secondArgument;
  _programPointer += 4;
}

void Program::handleINPUT(int input) {
  _program[_program[_programPointer + 1]] = input;
  _programPointer += 2;
}

void Program::handleOUTPUT() {
  //    std::cout << "[OUTPUT] " << _program[_program[_programPointer + 1]] <<
  //    std::endl;
  this->_output = _program[_program[_programPointer + 1]];
  _programPointer += 2;
}

void Program::handleJUMP_IF_TRUE(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  if (firstArgument != 0)
    _programPointer = secondArgument;
  else
    _programPointer += 3;
}

void Program::handleJUMP_IF_FALSE(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  if (firstArgument == 0)
    _programPointer = secondArgument;
  else
    _programPointer += 3;
}

void Program::handleLESS_THAN(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  if (firstArgument < secondArgument)
    _program[_program[_programPointer + 3]] = 1;
  else
    _program[_program[_programPointer + 3]] = 0;

  _programPointer += 4;
}

void Program::handleEQUALS(Instruction instruction) {
  int firstArgument{0};
  int secondArgument{0};

  if (instruction.firstArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    firstArgument = _program[_programPointer + 1];
  } else {
    firstArgument = _program[_program[_programPointer + 1]];
  }

  if (instruction.secondArgumentMode == ParameterMode::IMMEDIATE_MODE) {
    secondArgument = _program[_programPointer + 2];
  } else {
    secondArgument = _program[_program[_programPointer + 2]];
  }

  if (firstArgument == secondArgument)
    _program[_program[_programPointer + 3]] = 1;
  else
    _program[_program[_programPointer + 3]] = 0;

  _programPointer += 4;
}
