#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

struct paper
{
    paper(const std::vector<std::pair<int, int>>& dots, int x_max, int y_max);
    paper(const paper& other, char dir, int z);
    ~paper();
    void print();
    int w, h;
    bool** data;
};

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int x_max = 0, y_max = 0;
    std::vector<std::pair<int, int>> coords;

    // Get input
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty()) break;
        std::stringstream ss(line);
        std::string x_str, y_str;
        getline(ss, x_str, ',');
        getline(ss, y_str);
        int x = atoi(x_str.c_str());
        int y = atoi(y_str.c_str());
        x_max = x > x_max ? x : x_max;
        y_max = y > y_max ? y : y_max;
        coords.push_back(std::make_pair(x, y));
    }

    paper *p = new paper(coords, x_max, y_max);
    while (getline(std::cin, line))
    {
        std::stringstream ss(line);
        std::string str;
        getline(ss, str, '=');
        char dir = str.back();
        getline(ss, str);
        int z = atoi(str.c_str());
        
        paper* q = p;
        p = new paper(*p, dir, z);
        delete q;
    }

    p->print();

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

paper::paper(const std::vector<std::pair<int, int>>& dots, int x_max, int y_max)
    : w(x_max + 1), h(y_max + 1)
{
    data = new bool* [w];
    for (int i = 0; i < w; i++)
        data[i] = new bool[h] {false};
    for (const auto& dot : dots)
        data[dot.first][dot.second] = true;
}

paper::~paper()
{
    for (int i = 0; i < w; i++)
        delete[] data[i];
    delete[] data;
}

paper::paper(const paper& other, char dir, int z)
    : w(other.w), h(other.h)
{
    if (dir == 'x')
    {
        w = z;
        data = new bool* [w];
        for (int x = 0; x < w; x++)
            data[x] = new bool[h] {false};
        for (int x = 0; x < w; x++)
            for (int y = 0; y < h; y++)
                data[z - x - 1][y] = other.data[z - x - 1][y] | other.data[z + x + 1][y];
    }
    else
    {
        h = z;
        data = new bool* [w];
        for (int x = 0; x < w; x++)
            data[x] = new bool[h] {false};
        for (int x = 0; x < w; x++)
            for (int y = 0; y < h; y++)
                data[x][z - y - 1] = other.data[x][z - y - 1] | other.data[x][z + y + 1];
    }
}

void paper::print()
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            std::cout << (data[x][y] ? '*' : ' ');
        }
        std::cout << std::endl;
    }       
}