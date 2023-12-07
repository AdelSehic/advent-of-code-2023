#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

enum strength {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  FIVE_OF_A_KIND
};

std::unordered_map<char, int> cardStrength = {
    {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},  {'6', 5},  {'7', 6}, {'8', 7},
    {'9', 8}, {'T', 9}, {'J', 0}, {'Q', 11}, {'K', 12}, {'A', 13}};

class card {
private:
  char sym;
  int str;

public:
  card() = default;
  card(char c) : sym(c), str(cardStrength[c]){};
  int strength() const { return str; }
  char symbol() const { return sym; }
};

class hand {
private:
  card cards[5];
  int bet;
  int stren;

  int calc_strength() const {
    std::unordered_map<int, int> unique;
    int joker = 0;
    int max_repeats = 0, elem = 0, symbol = 0;
    for (int i = 0; i < 5; ++i) {
        /* std::cout << cards[i].symbol(); */
      if (cards[i].symbol() == 'J')
        ++joker;
      else {
        auto n = ++unique[this->cards[i].strength()];
        if (n > max_repeats) {
          max_repeats = n;
          elem = cards[i].strength();
          /* symbol = cards[i].symbol(); */
        }
      }
    }
    unique[elem] += joker;

    /* for (auto it : unique) */
    /*   std::cout << '\n' << it.first << ": " << it.second << ' '; */
    /* std::cout << "\tMost repeated: " << char(symbol) << " : " << max_repeats */
    /*           << std::endl << std::endl; */

    switch (unique.size()) {
    case 1:
      return FIVE_OF_A_KIND;
    case 2:
      for (const auto &entry : unique) {
        if (entry.second == 4)
          return FOUR_OF_A_KIND;
        else if (entry.second == 3)
          return FULL_HOUSE;
      }
      break;
    case 3:
      for (const auto &entry : unique) {
        if (entry.second == 3)
          return THREE_OF_A_KIND;
        else if (entry.second == 2)
          return TWO_PAIR;
      }
      break;
    case 4:
      return ONE_PAIR;
    default:
      return HIGH_CARD;
    }
    return HIGH_CARD;
  }

public:
  hand(std::string line) {
    for (int i = 0; i < 5; ++i) {
      cards[i] = card(line[i]);
    }
    stren = calc_strength();
    this->bet = std::stoi(line.substr(6));
  }

  int get_bet() const { return bet; }
  int strength() const { return stren; }

  bool operator<(const hand &other) const {
    if (strength() != other.strength())
      return strength() < other.strength();
    else
      for (int i = 0; i < 5; ++i) {
        if (cards[i].strength() != other.cards[i].strength())
          return cards[i].strength() < other.cards[i].strength();
      }
    return false;
  }

  void print() const {
    for (int i = 0; i < 5; ++i) {
      auto tmp = this->cards[i];
      std::cout << tmp.symbol();
    }
    std::cout << ' ' << this->bet << std::endl;
  }
};

int main() {

  std::vector<hand> game;
  std::ifstream is("input.txt");
  std::vector<std::string> input;
  std::string line;
  while (std::getline(is, line)) {
    hand h = hand(line);
    game.push_back(h);
  }

  std::sort(game.begin(), game.end());

  int sum = 0;
  for (auto i = 0; i < game.size(); ++i)
    sum += game.at(i).get_bet() * (i + 1);
  std::cout << sum << std::endl;

  return 0;
}

/* void print() { */
/*   for (int i = 0; i < 5; ++i) { */
/*     auto tmp = this->cards[i]; */
/*     std::cout << tmp.get_val(); */
/*   } */
/*   std::cout << ' ' << this->bet << std::endl; */
/* } */
