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
  std::string delimiter = "   ";
  std::string line;
  std::vector<int> numbers1;
  std::vector<int> numbers2;
  while (std::getline(file, line))
  {
    std::vector<std::string> tokens = split(line, delimiter);
    numbers1.push_back(std::stoi(tokens[0]));
    numbers2.push_back(std::stoi(tokens[1]));
  }
  std::sort(numbers1.begin(), numbers1.end());
  std::sort(numbers2.begin(), numbers2.end());

  int totalDistance = 0;
  for (int i = 0; i < numbers1.size(); i++)
    totalDistance += abs(numbers1[i] - numbers2[i]);
  std::cout << "totalDistance: " << totalDistance << "\n";
  return 0;
}
