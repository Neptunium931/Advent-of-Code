#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int mul(const std::string &s) {
  int result = 1;
  std::regex r("\\d+");
  std::smatch m;
  std::sregex_iterator it(s.begin(), s.end(), r);
  std::sregex_iterator end;
  for (; it != end; ++it) {
    result *= std::stoi(it->str());
  }
  return result;
}

std::vector<std::string> getAllMul(const std::string &s) {
  std::vector<std::string> find;
  std::regex r("(mul\\(\\d+,\\d+\\))|(do\\(\\))|(don't\\(\\))");
  std::smatch m;
  std::sregex_iterator it(s.begin(), s.end(), r);
  std::sregex_iterator end;
  for (; it != end; ++it) {
    find.push_back(it->str());
  }
  return find;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << argv[1] << std::endl;
    return 1;
  }
  std::string delimiter = " ";
  std::string line;
  int result = 0;
  auto count = true;
  while (std::getline(file, line)) {
    auto matchs = getAllMul(line);
    for (auto match : matchs) {
      if (match == "do()") {
        count = true;
        continue;
      }
      if (match == "don't()") {
        count = false;
        continue;
      }
      if (count) {
        result += mul(match);
      }
    }
  }
  std::cout << result << "\n";
  return 0;
}
