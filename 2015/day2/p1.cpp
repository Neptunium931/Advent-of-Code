#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int>
split(const std::string &s, const std::string &delimiter)
{
  std::vector<int> tokens;
  std::string s_copy = s; // Create a non-const copy of the input string
  size_t pos = 0;
  std::string token;
  while ((pos = s_copy.find(delimiter)) != std::string::npos)
  {
    token = s_copy.substr(0, pos);
    tokens.push_back(std::stoi(token));
    s_copy.erase(0, pos + delimiter.length());
  }
  tokens.push_back(std::stoi(s_copy));
  return tokens;
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
  std::string line;
  int nbCube = 0;
  while (std::getline(file, line))
  {
    // 2*l*w + 2*w*h + 2*h*l
    std::vector<int> tokens = split(line, "x");
    std::sort(tokens.begin(), tokens.end());
    const int l = tokens[0];
    const int w = tokens[1];
    const int h = tokens[2];
    nbCube += 3 * l * w + 2 * w * h + 2 * h * l;
  }
  std::cout << "Result: " << nbCube << std::endl;
  return 0;
}
