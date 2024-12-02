#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>
split(const std::string &s, const std::string &delimiter)
{
  std::vector<std::string> tokens;
  std::string s_copy = s; // Create a non-const copy of the input string
  size_t pos = 0;
  std::string token;
  while ((pos = s_copy.find(delimiter)) != std::string::npos)
  {
    token = s_copy.substr(0, pos);
    tokens.push_back(token);
    s_copy.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s_copy); // Add the remaining part of the string
  return tokens;
}

bool isSafe(std::vector<std::string> tokens) {
  bool isSafe = true;
  for (auto i = 2; i < tokens.size(); i++) {
    if (!isSafe) {
      continue;
    }
    auto x = std::stoi(tokens[i - 2]);
    auto y = std::stoi(tokens[i - 1]);
    auto z = std::stoi(tokens[i]);
    if ((x > y && y > z) || (x < y && y < z)) {
      if (std::abs(x - y) < 4 && std::abs(y - z) < 4) {
        isSafe = true;
        continue;
      }
    }
    isSafe = false;
  }
  return isSafe;
}

int
main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error opening file: " << argv[1] << std::endl;
    return 1;
  }
  std::string delimiter = " ";
  std::string line;
  int safe = 0;
  while (std::getline(file, line))
  {
    std::vector<std::string> tokens = split(line, delimiter);
    if (isSafe(tokens))
    {
      safe++;
      continue;
    }
    auto b=0;
    for (auto i = 0; i < tokens.size() && b==0; i++)
    {
      auto copy = tokens;
      copy.erase(copy.begin()+i,copy.begin()+i+1);
      if (isSafe(copy))
      {
        safe++;
        b=1;
        continue;
      }
    }
  }
  std::cout << safe << std::endl;
  return 0;
}