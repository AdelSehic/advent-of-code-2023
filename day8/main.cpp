#include <algorithm>
#include <fstream>
#include <iostream>
#include <pstl/glue_execution_defs.h>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<std::string> parse_line(const std::string &);

int main() {
  std::string line, directions, discard;
  std::unordered_map<std::string, std::pair<std::string, std::string>> map;

  std::ifstream is("input.txt");
  std::vector<std::string> input;
  std::getline(is, directions);
  std::getline(is, discard);
  while (std::getline(is, line)) {
    auto l = parse_line(line);
    map[l[0]] = std::make_pair(l[1], l[2]);
  }

  int counter = 0;
  auto d = directions.begin();
  for (auto it = map.find("AAA");;) {
    ++counter;
    if (d == directions.end())
      d = directions.begin();
    switch (*d++) {
    case 'R':
      it = map.find(it->second.second);
      break;
    case 'L':
      it = map.find(it->second.first);
      break;
    }
    if (it->first == "ZZZ")
      break;
  }
  std::cout << counter << std::endl;

  return 0;
}

std::vector<std::string> parse_line(const std::string &input) {
  std::vector<std::string> result(3);
  result[0] = input.substr(0, 3);
  result[1] = input.substr(7, 3);
  result[2] = input.substr(12, 3);
  return result;
}
