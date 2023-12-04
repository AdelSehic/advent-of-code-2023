#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {

  std::ifstream is("input.txt");
  std::istream_iterator<std::string> start(is), end;
  std::vector<std::string> input(start, end);
  std::unordered_map<int, int> repeat;

  int sum = 0, num_cards = 0;
  for (auto it = input.begin(); it != input.end();) {
    std::string card = (*(++it));
    int current = std::stoi(card.substr(0, card.size() - 1));
    if (!repeat[current]) ++repeat[current];

    std::unordered_set<std::string> winning;
    int wins = 0;

    while (*it != "|")
      winning.insert(*it++);

    while (*it != "Card" && it != input.end())
      if (winning.find(*it++) != winning.end())
        ++wins;

    for (int card = current + 1; card < current+wins+1; ++card) {
        if( !repeat[card] ) ++repeat[card];
        repeat[card] += 1 * repeat[current];
    }

    sum += std::pow(2, wins - 1) * repeat[current];
    num_cards += repeat[current];
  }

  std::cout << sum << " " << num_cards << std::endl;

  return 0;
}
