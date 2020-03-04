#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string fft2(std::string input, unsigned phasesCount) {
    std::string output = std::move(input);
    input.resize(output.size());

    for (unsigned phase = 0; phase < phasesCount; phase++) {
        std::cout << phase << std::endl;
        std::swap(output, input);

        for (int outputIndex = 0; outputIndex < input.size(); outputIndex++) {
            int result{0};
            int currentValue{1};

            for (int i = outputIndex; i < input.size(); i++) {
                int tmp{0};
                for (int j = i; j <= std::min(i + outputIndex, int(input.size() - 1)); j++) {
                    tmp += input[j] - 48;
                }

                switch (currentValue) {
                    case -1 :
                        result -= tmp;
                        break;
                    case 1 :
                        result += tmp;
                        break;
                    default:
                        break;
                }

                currentValue = -1 * currentValue;
                i += 2 * outputIndex + 1;
            }

            output[outputIndex] = (std::abs(result) % 10) + 48;
        }
    }

    return output.substr(0, 8);
}

int main() {
    std::string programInput{"59796737047664322543488505082147966997246465580805791578417462788780740484409625674676660947541571448910007002821454068945653911486140823168233915285229075374000888029977800341663586046622003620770361738270014246730936046471831804308263177331723460787712423587453725840042234550299991238029307205348958992794024402253747340630378944672300874691478631846617861255015770298699407254311889484508545861264449878984624330324228278057377313029802505376260196904213746281830214352337622013473019245081834854781277565706545720492282616488950731291974328672252657631353765496979142830459889682475397686651923318015627694176893643969864689257620026916615305397"};

    std::string s;
    s.reserve(programInput.size() * 10000);

    for (int i = 0; i < 10000; i++) {
        s += programInput;
    }

    std::cout << std::boolalpha << (fft2("12345678", 1) == "48226158") << std::endl;
    std::cout << std::boolalpha << (fft2("12345678", 2) == "34040438") << std::endl;
    std::cout << std::boolalpha << (fft2("12345678", 3) == "03415518") << std::endl;
    std::cout << std::boolalpha << (fft2("12345678", 4) == "01029498") << std::endl;

    std::cout << std::boolalpha << (fft2("80871224585914546619083218645595", 100) == "24176176") << std::endl;
    std::cout << std::boolalpha << (fft2("19617804207202209144916044189917", 100) == "73745418") << std::endl;
    std::cout << std::boolalpha << (fft2("69317163492948606335995924319873", 100) == "52432133") << std::endl;

    std::cout << fft2(s, 100)  << std::endl;

    return 0;
}
