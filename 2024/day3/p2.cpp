#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int
mul(const std::string &s)
{
  int result = 1;
  std::regex r("\\d+");
  std::sregex_iterator it(s.begin(), s.end(), r);
  std::sregex_iterator end;
  for (; it != end; ++it)
  {
    result *= std::stoi(it->str());
  }
  return result;
}

std::vector<std::string>
getAllMul(const std::string &s)
{
  std::vector<std::string> find;
  std::regex r("mul\\(\\d+,\\d+\\)");
  std::smatch m;
  std::sregex_iterator it(s.begin(), s.end(), r);
  std::sregex_iterator end;
  for (; it != end; ++it)
  {
    find.push_back(it->str());
  }
  return find;
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
  std::string allLine;
  int result = 0;
  while (std::getline(file, line))
  {
    allLine += line;
  }
  std::regex do("don't\\(\\)");
  std::regex dont("do\\(\\)");
  std::sregex_iterator itDo(line.begin(), line.end(), do);
  std::sregex_iterator endDo;
  std::sregex_iterator itDont(line.begin(), line.end(), dont);
  std::sregex_iterator endDont;

  std::vector<int> enabled;
  std::vector<int> disabled;
  for (; itDo != endDo; ++itDo)
  {
    enabled.push_back(itDo->position());
  }
  for (; itDont != endDont; ++itDont)
  {
    disabled.push_back(itDont->position());
  }

  auto matchs = getAllMul(allLine);
  for (auto match : matchs)
  {
    result += mul(match);
  }
  std::cout << result << "\n";
  return 0;
}
