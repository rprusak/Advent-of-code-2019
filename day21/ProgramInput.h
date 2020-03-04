#ifndef DAY21_PROGRAMINPUT_H
#define DAY21_PROGRAMINPUT_H

#include <string>
#include "ProgramInputInterface.h"


class ProgramInput: public ProgramInputInterface {
public:
    char getValue() override;

private:
    std::string _currentInput;
    std::string::iterator _currentPosition;
};


#endif