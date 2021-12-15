#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> data;
std::vector<std::vector<bool>> visited;
int maxi, maxj;

// Depth first search to count and mark as visited the squares in a basin.
int dfs(int i, int j)
{
    if (i < 0 || i > maxi || j < 0 || j > maxj || visited[i][j] || data[i][j] == '9')
        return 0;
    visited[i][j] = true;
    return 1 + dfs(i - 1, j) + dfs(i + 1, j) + dfs(i, j - 1) + dfs(i, j + 1);
}

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    // Fetch input
    std::string str;
    while (std::cin >> str)
        data.push_back(str);
    visited = std::vector<std::vector<bool>>(data.size(), std::vector<bool>(data[0].size(), false));

    // Build an array containing the sizes of all basins (uses depth-first search)
    std::vector<int> basins;
    maxi = data.size() - 1;
    maxj = data[0].size() - 1;
    for (int i = 0; i <= maxi; i++)
    {
        for (int j = 0; j <= maxj; j++)
        {
            int tmp = dfs(i, j);
            if (tmp) basins.push_back(tmp);
        }
    }

    // Reverse sort the array, so largest basins are in front.
    std::sort(basins.rbegin(), basins.rend());

    // Output
    std::cout << basins[0]*basins[1]*basins[2] << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
