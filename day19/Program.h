#ifndef DAY07_PROGRAM_H
#define DAY07_PROGRAM_H

#include <vector>
#include <string>
#include "ProgramMemory.h"

class Program {
public:
    explicit Program(const std::string& inputProgram);

    long run(long x, long y);

    bool isHalted() const {
        return _isHalted;
    }

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
        ADJUST_BASE,
        HALT
    };

    enum class ParameterMode {
        POSITION_MODE,
        IMMEDIATE_MODE,
        RELATIVE_MODE
    };

    struct Instruction {
        OperationCode operationCode;
        ParameterMode firstArgumentMode;
        ParameterMode secondArgumentMode;
        ParameterMode thirdArgumentMode;
    };

    ProgramMemory _program;
    long _output;

private:
    size_t _programPointer;
    long _relativeBase;
    bool _isHalted;


    static std::vector<long> convertProgramToInts(const std::string& inputProgram);
    static Instruction intToInstruction(long value);
    static OperationCode readOperationCode(long value);
    static ParameterMode readParameterMode(long value, long parameterNumber);

    void handleADD(Instruction instruction);
    void handleMULTIPLY(Instruction instruction);
    void handleINPUT(Instruction instruction, long input);
    void handleOUTPUT(Instruction instruction);
    void handleJUMP_IF_TRUE(Instruction instruction);
    void handleJUMP_IF_FALSE(Instruction instruction);
    void handleLESS_THAN(Instruction instruction);
    void handleEQUALS(Instruction instruction);
    void handleADJUST_BASE(Instruction instruction);

    long readArgument(ParameterMode mode, size_t position);
    long readArgumentAsAddress(ParameterMode mode, size_t position);
};


#endif //DAY07_PROGRAM_H
