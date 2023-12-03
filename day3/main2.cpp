#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

int find_gears(const std::vector<std::string> &input, int i, int j) {
  int sum = 1;
  std::string temp = "";
  std::unordered_set<int> nums;

  int directions[8][2] = {
      {-1, 0},  {1, 0},  {0, -1}, {0, 1}, // horizontal and vertical
      {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // diagonal
  };

  for (auto [a, b] : directions) {
    if (isdigit(input[i + a][j + b])) {
      int r = j + b, l = j + b;
      for (int start = j + b; isdigit(input[i + a][start]); --start)
        l = start;
      for (int start = j + b; isdigit(input[i + a][start]); ++start)
        r = start;
      temp = input[i + a].substr(l, r - l + 1);
    }
    if (temp.size()) {
      if (!isdigit(temp.front()))
        temp = temp.substr(1, temp.size() - 1);
      if (!isdigit(temp.back()))
        temp.pop_back();
      nums.emplace(std::stoi(temp));
    }
  }

  if (nums.size() <= 1)
    return 0;

  for (auto n : nums)
    sum *= n;
  

  return sum;
}

int main() {

  std::ifstream is("input.txt");
  std::vector<std::string> input;
  std::string line;
  input.push_back("");
  while (std::getline(is, line)) {
    input.push_back("." + line + ".");
  }
  input[0] = std::string(input[1].size(), '.');
  input.push_back(std::string(input[1].size(), '.'));

  int sum = 0;
  for (auto i = 0; i < input.size(); ++i) {
    for (auto j = 0; j < input[i].size(); ++j) {
      if (input[i][j] == '*') {
        sum += find_gears(input, i, j);
      }
    }
  }
  std::cout << sum << std::endl;

  return 0;
}
