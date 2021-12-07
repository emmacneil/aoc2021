#include <chrono>
#include <iostream>
#include <stdint.h>
#include <vector>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    // Get the input.
    // Also keep track of the largest position number.
    std::vector<int> positions;
    int max_pos = 0;
    for (int n; std::cin >> n;)
    {
        max_pos = n > max_pos ? n : max_pos;
        positions.push_back(n);
        if (std::cin.peek() == ',')
            std::cin.ignore();
    }

    // Compute the cost of moving all crabs to a given position
    std::vector<uint64_t> costs(max_pos + 1, 0);
    for (size_t i = 0; i < costs.size(); i++)
        for (size_t j = 0; j < positions.size(); j++)
            costs[i] += positions[j] > i ? (uint64_t)positions[j] - (uint64_t)i : (uint64_t)i - (uint64_t)positions[j];

    // Find position of least cost.
    size_t pos = 0;
    uint64_t cost = 0x7fffffff;
    for (size_t i = 0; i < costs.size(); i++)
    {
        if (costs[i] < cost)
        {
            cost = costs[i];
            pos = i;
        }
    }

    // Output
    std::cout << cost << " (position " << pos << ")" << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}