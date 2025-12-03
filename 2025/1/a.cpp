#include <fstream>
#include <iostream>
#include <print>

enum class Direction
{
  Left = -1,
  Right = 1
};

const auto calc = [](auto base, auto offset, Direction direction)
{
  auto result = base + offset * static_cast<int>(direction);
  return result % 100;
};

int
main(int argc, char *argv[])
{
  auto input = std::ifstream(argv[1]);

  auto line = std::string();
  auto base = 50;
  auto numberOfZeros = 0;
  while (std::getline(input, line))
  {
    auto offset = std::stoi(line.substr(1));
    if (line[0] == 'L')
    {
      base = calc(base, offset, Direction::Left);
    }
    else
    {
      base = calc(base, offset, Direction::Right);
    }
    if (base == 0)
      ++numberOfZeros;
    std::println("base: {}, offset: {}, direction: {}, result: {}",
                 base,
                 offset,
                 line[0],
                 base);
  }
  std::println("number of zeros: {}", numberOfZeros);

  return 0;
}
