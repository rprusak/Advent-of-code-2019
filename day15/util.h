#ifndef DAY03_UTIL_H
#define DAY03_UTIL_H

#include <string>
#include <vector>

class util {
 public:
  static std::vector<std::string> split(const std::string& s, char delim);

  static std::vector<std::string> readInput(const char* filename);
};

#endif  // DAY03_UTIL_H
