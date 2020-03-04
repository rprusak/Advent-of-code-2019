#ifndef DAY09_PROGRAMMEMORY_H
#define DAY09_PROGRAMMEMORY_H

#include <vector>
#include <unordered_map>

class ProgramMemory {
public:
    ProgramMemory(const std::vector<long> &program);

    std::vector<long>::size_type size() const {
        return _program.size();
    }

    long& operator[](std::vector<long>::size_type index);

private:
    std::vector<long> _program;
    std::unordered_map<std::vector<long>::size_type, long> _additionalMemory;
};


#endif //DAY09_PROGRAMMEMORY_H
