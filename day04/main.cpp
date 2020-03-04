#include <iostream>
#include <string>

bool isNotDecreasing(unsigned long value) {
    auto str = std::to_string(value);
    for (size_t i = 0; i < str.size() - 1; i++) {
        if (str[i] - 48 > str[i + 1] - 48)
            return false;
    }

    return true;
}

bool hasSameTwoValuesInRow(unsigned long value) {
    auto str = std::to_string(value);
    for (size_t i = 0; i < str.size() - 1; i++) {
        if (str[i] == str[i + 1])
            return true;
    }

    return false;
}

bool hasOnlySameTwoValuesInRow(unsigned long value) {
    auto str = std::to_string(value);

    bool doubleFound{false};
    size_t currentIndex{0};
    size_t currentCounter{1};

    while (currentIndex < str.size()) {
        if (str[currentIndex] == str[currentIndex + 1]) {
            currentCounter++;
        } else {
            if (currentCounter == 2)
                doubleFound = true;
            currentCounter = 1;
        }
        currentIndex++;
    }

    if (currentCounter == 2)
        doubleFound = 2;

    return doubleFound;
}

int main() {
    unsigned long start{402328};
    unsigned long end{864247};
    unsigned long counter{0};

    for (unsigned long i = start; i <= end; i++) {
        if (hasSameTwoValuesInRow(i) && isNotDecreasing(i) && hasOnlySameTwoValuesInRow(i))
            counter++;
    }

    std::cout << counter << std::endl;

    std::cout << hasOnlySameTwoValuesInRow(112233) << std::endl;
    std::cout << hasOnlySameTwoValuesInRow(123444) << std::endl;
    std::cout << hasOnlySameTwoValuesInRow(111122) << std::endl;


    return 0;
}
