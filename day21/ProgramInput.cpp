#include "ProgramInput.h"
#include <iostream>

char ProgramInput::getValue() {
    if (_currentInput.empty()) {
        std::cout << "input>" << std::endl;
        std::getline(std::cin, _currentInput);
        _currentPosition = _currentInput.begin();
    }

    if (_currentPosition == _currentInput.end()) {
        _currentInput.clear();
        return '\n';
    }

    char value = *_currentPosition;
    _currentPosition++;
    return value;
}
