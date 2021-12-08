#include "line.hpp"

#include <chrono>
#include <iostream>
#include <vector>

/* I took some extra time to try implementing a custom iterator. Notice the range-based for loops
 * below.
 */

int main (int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int x1, y1, x2, y2, max_x = 0, max_y = 0;
    std::vector<line> lines;

    // Read in all the lines from stdin
    // In part 1, we can ignore diagonal lines.
    while (std::cin >> x1)
    {
        std::cin.ignore(1);
        std::cin >> y1;
        std::cin.ignore(4);
        std::cin >> x2;
        std::cin.ignore(1);
        std::cin >> y2;

        // Skip diagonal lines
        if ((x1 != x2) && (y1 != y2)) continue;

        line l(x1, y1, x2, y2);
        lines.push_back(l);

        // Find the largest integers needed to represent the lines coordinates
        max_x = x1 > max_x ? x1 : max_x;
        max_x = x2 > max_x ? x2 : max_x;
        max_y = y1 > max_y ? y1 : max_y;
        max_y = y2 > max_y ? y2 : max_y;
    }

    // Construct a large enough grid
    int grid[max_x][max_y] = {0};

    // Plot the lines on a grid
    int count = 0;
    for (line& l : lines)
    {
        for (auto p : l) // A little Chrismas elf magic
        {
            if (grid[p.x][p.y] == 1)
                count++;
            grid[p.x][p.y]++;
        }
    }

    // Output
    std::cout << count << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;
    return 0;
}
