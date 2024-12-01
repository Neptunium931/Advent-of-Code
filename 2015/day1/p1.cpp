#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

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
  std::getline(file, line);
  int floor = 0;
  for (auto i = 0; i < line.size(); ++i)
  {
    if (line[i] == '(')
      floor++;
    if (line[i] == ')')
      floor--;
  }
  std::cout << "Floor: " << floor << std::endl;
  return 0;
}
