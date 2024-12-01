#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

using cordone = std::pair<int, int>;

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
  int nbHose = 0;
  std::map<cordone, int> cordones;
  cordone s = { 0, 0 };
  cordone r = { 0, 0 };
  for (int i = 0; i < line.length(); i++)
  {
    cordone &c = (i % 2 == 0) ? s : r;
    switch (line[i])
    {
      case '>':
        c.first++;
        break;
      case '<':
        c.first--;
        break;
      case '^':
        c.second++;
        break;
      case 'v':
        c.second--;
        break;
    }
    cordones[c]++;
  }
  nbHose = cordones.size();
  std::cout << "Result: " << nbHose << std::endl;
  return 0;
}
