#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

int shrink(int x, int w)
{
    w = w + 1;
    int ret = x % w;
    if ((x / w) & 1) ret = w - ret - 2;
    return ret;
}

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int x_max = 0, y_max = 0;
    std::vector<std::pair<int, int>> coords;

    // Get dot coordinates
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty()) break;
        std::stringstream ss(line);
        std::string x_str, y_str;
        getline(ss, x_str, ',');
        getline(ss, y_str);
        coords.push_back(std::make_pair(atoi(x_str.c_str()), atoi(y_str.c_str())));
    }

    int w = 0, h = 0;
    while (getline(std::cin, line))
    {
        char ch = line[11];
        if (ch == 'x')
            w = atoi(line.c_str() + 13);
        else
            h = atoi(line.c_str() + 13);
    }
    bool** out = new bool*[w];
    for (int x = 0; x < w; x++)
        out[x] = new bool[h] {false};

    for (const auto& pr : coords)
        out[shrink(pr.first, w)][shrink(pr.second, h)] = true;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
            std::cout << (out[x][y] ? '*' : ' ');
        std::cout << std::endl;
    }

    for (int x = 0; x < w; x++)
        delete[] out[x];
    delete[] out;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;
    // Seems like roughly half the elapsed time is cleanup and printing.

    return 0;
}
