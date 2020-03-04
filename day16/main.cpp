#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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
        for (int j = i; j <= std::min(i + outputIndex, int(input.size() - 1));
             j++) {
          tmp += input[j] - 48;
        }

        switch (currentValue) {
          case -1:
            result -= tmp;
            break;
          case 1:
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
  std::string programInput{
      "597967370476643225434885050821479669972464655808057915784174627887807404"
      "844096256746766609475415714489100070028214540689456539114861408231682339"
      "152852290753740008880299778003416635860466220036207703617382700142467309"
      "360464718318043082631773317234607877124235874537258400422345502999912380"
      "293072053489589927940244022537473406303789446723008746914786318466178612"
      "550157702986994072543118894845085458612644498789846243303242282780573773"
      "130298025053762601969042137462818302143523376220134730192450818348547812"
      "775657065457204922826164889507312919743286722526576313537654969791428304"
      "598896824753976866519233180156276941768936439698646892576200269166153053"
      "97"};

  std::string s;
  s.reserve(programInput.size() * 10000);

  for (int i = 0; i < 10000; i++) {
    s += programInput;
  }

  std::cout << std::boolalpha << (fft2("12345678", 1) == "48226158")
            << std::endl;
  std::cout << std::boolalpha << (fft2("12345678", 2) == "34040438")
            << std::endl;
  std::cout << std::boolalpha << (fft2("12345678", 3) == "03415518")
            << std::endl;
  std::cout << std::boolalpha << (fft2("12345678", 4) == "01029498")
            << std::endl;

  std::cout << std::boolalpha
            << (fft2("80871224585914546619083218645595", 100) == "24176176")
            << std::endl;
  std::cout << std::boolalpha
            << (fft2("19617804207202209144916044189917", 100) == "73745418")
            << std::endl;
  std::cout << std::boolalpha
            << (fft2("69317163492948606335995924319873", 100) == "52432133")
            << std::endl;

  std::cout << fft2(s, 100) << std::endl;

  return 0;
}
