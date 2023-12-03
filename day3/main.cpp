#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

#define insert_begin                                                           \
  surround[input[i - 1][j - 1]] = std::make_pair(i - 1, j - 1);                \
  surround[input[i][j - 1]] = std::make_pair(i, j - 1);                        \
  surround[input[i + 1][j - 1]] = std::make_pair(i + 1, j - 1);

#define insert_cur                                                             \
  surround[input[i - 1][j]] = std::make_pair(i - 1, j);                        \
  surround[input[i + 1][j]] = std::make_pair(i + 1, j);

#define insert_end                                                             \
  surround[input[i + 1][j]] = std::make_pair(i + 1, j);                        \
  surround[input[i - 1][j]] = std::make_pair(i - 1, j);                        \
  surround[input[i][j]] = std::make_pair(i, j);                                \

int main() {

  std::ifstream is("test.txt");
  std::vector<std::string> input;
  std::string line;
  input.push_back("");
  while (std::getline(is, line)) {
    input.push_back("." + line + ".");
  }
  input[0] = std::string(input[1].size(), '.');
  input.push_back(std::string(input[1].size(), '.'));

  int sum = 0;
  std::unordered_map<std::pair<int, int>, int, pairhash> gears;
  std::unordered_map<char, std::pair<int, int>> surround;
  int curdig = 0;
  for (auto i = 0; i < input.size(); ++i) {
    for (auto j = 0; j < input[0].size(); ++j) {
      if (isdigit(input[i][j])) {
        curdig = (curdig * 10) + (input.at(i).at(j) - '0');
        if (!isdigit(input[i][j - 1])) {
          insert_begin;
        }
        insert_cur;
      } else if (curdig) {
        insert_end;

        /* for (auto [k, v] : surround) { */
        /*     if(k == '*'){ */
        /*         gears.insert(std::make_pair(1, 5)); */
        /*     } */
        /*     printf("%d:%d - %s\n", v.first, v.second, &k ); */
        /* } */

        if (surround.size() > 1)
          sum += curdig;
        curdig = 0;
        surround.clear();
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
