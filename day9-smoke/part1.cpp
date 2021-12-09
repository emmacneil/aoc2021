#include <chrono>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    // Fetch input
    std::vector<std::string> data;
    std::string str;
    while (std::cin >> str)
        data.push_back(str);

    int sum = 0, maxi = data.size() - 1, maxj = data[0].size() - 1;
    for (int i = 0; i <= maxi; i++)
        for (int j = 0; j <= maxj; j++)
            if (   ((i == 0)    || (data[i][j] < data[i-1][j]))
                && ((i == maxi) || (data[i][j] < data[i+1][j]))
                && ((j == 0)    || (data[i][j] < data[i][j-1]))
                && ((j == maxj) || (data[i][j] < data[i][j+1])) )
                sum += (int)(data[i][j] - '0' + 1);

    // Output
    std::cout << sum << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
