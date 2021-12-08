#include "line.hpp"

#include <chrono>
#include <iostream>
#include <vector>

/* I took some extra time to try implementing a custom iterator. Notice the range-based for loops
 * below.
 *
 * This solution is also more general than the problem demands. It accounts also for lines that are
 * diagonal but not at 45 degrees, though still restricted to integer coordinates. It would count,
 * e.g., the intersection at (1,2) of the lines (0,0) -> (2,4) and (0,4) -> (2,0).
 */

int main (int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int x1, y1, x2, y2, max_x = 0, max_y = 0;
    std::vector<line> lines;

    // Read in all the lines from stdin
    while (std::cin >> x1)
    {
        std::cin.ignore(1);
        std::cin >> y1;
        std::cin.ignore(4);
        std::cin >> x2;
        std::cin.ignore(1);
        std::cin >> y2;

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
