#include "geometry.hpp"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <set>
#include <sstream>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::vector<std::vector<triple>> solved_scanners, unsolved_scanners;

    // Get input
    std::string line;
    while (getline(std::cin, line))
    {
        unsolved_scanners.emplace_back();
        while (getline(std::cin, line))
        {
            if (line.empty()) break;
            for (auto & ch : line)
                if (ch == ',')
                    ch = ' ';

            triple t;
            std::stringstream ss(line);
            ss >> std::get<0>(t) >> std::get<1>(t) >> std::get<2>(t);
            unsolved_scanners.back().push_back(t);
        }
    }

    solved_scanners.push_back(unsolved_scanners.front());
    unsolved_scanners.erase(unsolved_scanners.begin());

    for (size_t i = 0; i < solved_scanners.size(); i++)
    {
        for (size_t j = 0; j < unsolved_scanners.size(); j++)
        {
            auto solved = solved_scanners.begin() + i;
            auto unsolved = unsolved_scanners.begin() + j;
            bool found = false;
            for (rotation r : rotations)
            {
                std::optional<triple> t = get_translation(*solved, *unsolved, r);
                if (t)
                {
                    found = true;

                    std::vector<triple> new_solution;
                    for (const triple &p : *unsolved)
                        new_solution.push_back(r(p) - *t);
                    unsolved_scanners.erase(unsolved);
                    solved_scanners.push_back(new_solution);

                    break;
                }
            }
            if (found) j--;
        }
    }

    assert(unsolved_scanners.size() == 0);

    // Stick all the points in a set and count the number of unique points.
    std::set<triple> S;
    for (auto v : solved_scanners)
        S.insert(v.begin(), v.end());
    std::cout << S.size() << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
