#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

class Set {
private:
  std::unordered_map<std::string, int> cubes;

public:
  Set(std::string line) {
    std::stringstream temp{line};
    while (std::getline(temp, line, ',')) {
      if (line[0] == ' ')
        line = line.substr(1);
      auto delim = line.find(" ");
      cubes[line.substr(delim + 1)] += std::stoi(line.substr(0, delim));
    }
  }

  bool is_possible(const std::unordered_map<std::string, int> &max_values) {
    for (auto [k, v] : this->cubes) {
      if (v > max_values.at(k)) {
        return false;
      }
    }
    return true;
  }

  int blue() { return cubes["blue"]; }
  int red() { return cubes["red"]; }
  int green() { return cubes["green"]; }
};

class Game {
  std::vector<Set> sets;
  int id, maxred = 1 , maxblue = 1, maxgreen = 1;

public:
  Game(std::string line) {
    int d1 = line.find(' '), d2 = line.find(':');
    id = std::stoi(line.substr(d1, d2 - d1));

    std::stringstream cubes{line.substr(line.find(':') + 1)};
    while (std::getline(cubes, line, ';')) {
      sets.push_back(Set{line.substr(1)});
    }
  }

  bool is_possible(const std::unordered_map<std::string, int> &max_values) {
    for (auto set : this->sets) {
      if (!set.is_possible(max_values))
        return false;
    }
    return true;
  }

  int power() { 
  
    for ( auto set : this->sets ) {
        if ( set.blue() > maxblue ) maxblue = set.blue();
        if ( set.red() > maxred ) maxred = set.red();
        if ( set.green() > maxgreen ) maxgreen = set.green();
    }

    return maxred * maxblue * maxgreen; 
  }

  int get_id() { return this->id; }
};

int main() {
  std::unordered_map<std::string, int> max_values{
      {"red", 12}, {"green", 13}, {"blue", 14}};
  int sum = 0, power = 0;

  std::ifstream is("input.txt");
  std::vector<std::string> input;
  std::string line;
  while (std::getline(is, line)) {
    auto game = Game{line};
    if (game.is_possible(max_values))
      sum += game.get_id();
    power += game.power();
  }

  std::cout << sum << ", " << power << std::endl;

  return 1;
}
