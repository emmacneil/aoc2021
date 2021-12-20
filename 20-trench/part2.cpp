#include "automata.hpp"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    const int n_rounds = 50;

    // Get rules input
    std::vector<bool> rules;
    std::string line;
    std::cin >> line;
    for (char ch : line)
        rules.push_back(ch == '#');
    assert(rules.size() == 512);

    // Ignore empty line
    std::cin.ignore(1);
    
    // Get cell input. Assumes starting state is given as a square a grid (not rectangular)
    std::cin >> line;
    size_t w = line.size();
    std::vector<std::vector<bool>> cells(w, std::vector<bool>(w, false));
    for (size_t i = 0; i < w; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            cells[i][j] = (line[j] == '#');
        }
        std::cin >> line;
    }

    for (int i = 1; i <= n_rounds; i++)
        sim(cells, rules, i);
    std::cout << count_cells(cells) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
