#include <chrono>
#include <iostream>
#include <stdint.h>
#include <string>
#include <queue>

uint8_t data[10][10];
uint8_t n_rounds = 100;

uint8_t incr(uint8_t i, uint8_t j);
uint32_t sim();

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    // Get input
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            char ch;
            std::cin >> ch;
            data[i][j] = (uint8_t)(ch - '0');
        }
    }

    uint32_t round = 1;
    while (sim() < 100)
        round++;

    // Output
    std::cout << round << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

/* Validate the row and column, increase the energy level by one, return the new energy level. */
uint8_t incr(uint8_t i, uint8_t j)
{
    if (i >= 10 || j >= 10) return 0;
    return ++data[i][j];
}

/* Simulate one round of charging octopuses. Return the number of flashes that occured this round. */
uint32_t sim()
{
    uint32_t ret = 0;
    std::queue<std::pair<uint8_t, uint8_t>> to_flash;

    for (uint8_t i = 0; i < 10; i++)
    {
        for (uint8_t j = 0; j < 10; j++)
        {
            if (data[i][j] > 9)
                data[i][j] = 0;
            if (incr(i, j) == 10)
                to_flash.push(std::make_pair(i, j));
        }
    }
    while (!to_flash.empty())
    {
        uint8_t i = to_flash.front().first;
        uint8_t j = to_flash.front().second;
        to_flash.pop();
        ret++;

        if (incr(i - 1, j - 1) == 10) to_flash.push(std::make_pair(i - 1, j - 1));
        if (incr(i - 1, j    ) == 10) to_flash.push(std::make_pair(i - 1, j    ));
        if (incr(i - 1, j + 1) == 10) to_flash.push(std::make_pair(i - 1, j + 1));
        if (incr(i    , j - 1) == 10) to_flash.push(std::make_pair(i    , j - 1));
        if (incr(i    , j + 1) == 10) to_flash.push(std::make_pair(i    , j + 1));
        if (incr(i + 1, j - 1) == 10) to_flash.push(std::make_pair(i + 1, j - 1));
        if (incr(i + 1, j    ) == 10) to_flash.push(std::make_pair(i + 1, j    ));
        if (incr(i + 1, j + 1) == 10) to_flash.push(std::make_pair(i + 1, j + 1));
    }

    return ret;
}
