#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, int> digits{
    {"1", 1},     {"2", 2},     {"3", 3},    {"4", 4},    {"5", 5},
    {"6", 6},     {"7", 7},     {"8", 8},    {"9", 9},    {"one", 1},
    {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6},
    {"seven", 7}, {"eight", 8}, {"nine", 9}};

int find_num(const std::string &line) {
  int left_most = line.size(), right_most = 0;
  int left = 0, right = 0;

  for (auto [str, dig] : digits) {
    int index = line.find(str);
    if (index != std::string::npos && index < left_most) {
      left_most = index;
      left = dig;
    }
    index = line.rfind(str);
    if (index != std::string::npos && index > right_most) {
      right_most = index;
      right = dig;
    }
  }

  if (left_most == right_most)
    right = left;

  return 10 * left + right;
}

int main() {
  int sum = 0;
  std::ifstream is("input.txt");
  std::istream_iterator<std::string> start(is), end;
  std::vector<std::string> input(start, end);

  for (auto line : input) {
    sum += find_num(line);
  }
  
  std::cout << sum << std::endl;
}
