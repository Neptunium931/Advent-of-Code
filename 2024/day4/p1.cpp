#include <iostream>
#include <vector>
#include <fstream>
#include <string>

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool checkDirection(const std::vector<std::string>& grid, int x, int y, int dx, int dy) {
    std::string word = "XMAS";
    for (int i = 0; i < 4; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (!isValid(nx, ny, grid.size(), grid[0].size()) || grid[nx][ny] != word[i]) {
            return false;
        }
    }
    return true;
}

int findXmas(const std::vector<std::string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    std::vector<std::pair<int, int>> directions = {
        {1, 0},  // Down
        {-1, 0}, // Up
        {0, 1},  // Right
        {0, -1}, // Left
        {1, 1},  // Down-Right
        {1, -1}, // Down-Left
        {-1, 1}, // Up-Right
        {-1, -1} // Up-Left
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (const auto& dir : directions) {
                if (checkDirection(grid, i, j, dir.first, dir.second)) {
                    count++;
                }
            }
        }
    }
    return count;
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
  std::vector<std::string> grid;
  std::string line;
  while (std::getline(file,line))
  {
      grid.push_back(line);
  }
  

  int result = findXmas(grid);
  std::cout << "Number of occurrences of 'XMAS': " << result
       << std::endl; // Output should be 18
  return 0;
}