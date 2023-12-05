#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::ifstream is("input.txt");
  std::istream_iterator<std::string> start(is), end;
  std::vector<std::string> input(start, end);
  auto it = input.begin() + 1;

  std::unordered_map<long int, long int> seeds;
  while (isdigit(it->at(0))) {
    auto seed_start = std::stol(*it++);
    auto seed_length = std::stol(*it++);
    for (auto i = seed_start; i < seed_start + seed_length; ++i)
      seeds[i] = i;
  }

  while (it != input.end()) {
    ++ ++it;
    std::unordered_map<long, long> assigns;
    while (it != input.end() && isdigit(it->at(0))) {
      auto dest = std::stol(*it++), src = std::stol(*it++),
           range = std::stol(*it++);
      for (auto [k, v] : seeds) {
        if (v >= src && v < src + range)
          assigns[k] = dest + v - src;
      }
    }
    for (auto [k, v] : assigns)
      seeds[k] = v;
  }

  auto min = seeds.begin()->second;
  for (auto [k, v] : seeds)
    if (v < min)
      min = v;
  
  std::cout << "MIN: " << min << std::endl;

  return 0;
}

/*
Seed 14,  soil 14,
fertilizer 53,
water 49,
light 42, temperature 42,
humidity 43, location 43.


  std::vector<std::string> names{"Seed",  "Soil", "Fert",  "Water",
                                 "Light", "Temp", "Humid", "location"};
  int i = 0;
*/
