#ifndef DAY07_PROGRAM_H
#define DAY07_PROGRAM_H

#include <string>
#include <vector>

class Program {
 public:
  explicit Program(const std::string& inputProgram);

  int run(const std::vector<int>& inputValues);

  bool isHalted() const { return _ishalted; }

 private:
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

  enum class ParameterMode { POSITION_MODE, IMMEDIATE_MODE };

  struct Instruction {
    OperationCode operationCode;
    ParameterMode firstArgumentMode;
    ParameterMode secondArgumentMode;
    ParameterMode thirdArgumentMode;
  };

  std::vector<int> _program;
  int _output;
  size_t _programPointer;
  bool _ishalted;

  static std::vector<int> convertProgramToInts(const std::string& inputProgram);
  static Instruction intToInstruction(int value);
  static OperationCode readOperationCode(int value);
  static ParameterMode readParameterMode(int value, int parameterNumber);

  void handleADD(Instruction instruction);
  void handleMULTIPLY(Instruction instruction);
  void handleINPUT(int input);
  void handleOUTPUT();
  void handleJUMP_IF_TRUE(Instruction instruction);
  void handleJUMP_IF_FALSE(Instruction instruction);
  void handleLESS_THAN(Instruction instruction);
  void handleEQUALS(Instruction instruction);
};

#endif  // DAY07_PROGRAM_H
