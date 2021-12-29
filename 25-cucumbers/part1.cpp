#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line;
    std::vector<std::string> input;
    while (std::cin >> line)
        input.push_back(line);

    size_t width = input[0].size();
    size_t height = input.size();
    size_t size = width * height;

    char** grid, ** grid_cpy;
    grid = new char* [height];
    grid_cpy = new char* [height];
    grid[0] = new char[size]{ 0 };
    grid_cpy[0] = new char[size]{ 0 };
    for (int i = 1; i < height; i++)
    {
        grid[i] = grid[i - 1] + width;
        grid_cpy[i] = grid_cpy[i - 1] + width;
    }

    for (int i = 0; i < height; i++)
    {
        memcpy(grid[i], input[i].data(), width);
        std::cin >> line;
    }

    bool changed = true;
    int steps = 0;
    while (changed)
    {
        changed = false;
        steps++;
        memcpy(grid_cpy[0], grid[0], size);
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                size_t J = (j + 1 == width) ? 0 : j + 1;
                if (grid[i][j] == '>' && grid[i][J] == '.')
                {
                    changed = true;
                    grid_cpy[i][j] = '.';
                    grid_cpy[i][J] = '>';
                }
            }
        }

        memcpy(grid[0], grid_cpy[0], size);
        for (size_t i = 0; i < height; i++)
        {
            size_t I = (i + 1 == height) ? 0 : i + 1;
            for (size_t j = 0; j < width; j++)
            {
                if (grid_cpy[i][j] == 'v' && grid_cpy[I][j] == '.')
                {
                    changed = true;
                    grid[i][j] = '.';
                    grid[I][j] = 'v';
                }
            }
        }
    }

    std::cout << steps << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
