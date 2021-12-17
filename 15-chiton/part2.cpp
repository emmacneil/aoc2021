#include <assert.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<uint16_t, uint16_t, uint16_t> node;

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line;
    std::cin >> line;
    size_t inner_width = line.size();
    size_t outer_width = 5 * inner_width;

    uint8_t** costs;
    costs = new uint8_t * [outer_width];
    costs[0] = new uint8_t[outer_width * outer_width]{ 0 };
    uint16_t** totals;
    totals = new uint16_t * [outer_width];
    totals[0] = new uint16_t[outer_width * outer_width];
    bool** visited;
    visited = new bool * [outer_width];
    visited[0] = new bool[outer_width * outer_width]{ 0 };

    for (size_t i = 1; i < outer_width; i++)
    {
        costs[i] = costs[i - 1] + outer_width;
        visited[i] = visited[i - 1] + outer_width;
        totals[i] = totals[i - 1] + outer_width;
    }
    memset(totals[0], 0x7fff, sizeof(uint16_t) * outer_width * outer_width);

    int row = 0;
    do
    {
        for (size_t i = 0; i < inner_width; i++)
            costs[row][i] = (uint8_t)(line[i] - '0');
        row++;
    } while (std::cin >> line);
    // Assume the input data is a square grid
    assert(row == inner_width);

    for (size_t i = 0; i < inner_width; i++)
    {
        for (size_t j = 0; j < inner_width; j++)
        {
            for (size_t I = 0; I < 5; I++)
            {
                for (size_t J = 0; J < 5; J++)
                {
                    uint16_t val = costs[i][j] + I + J;
                    if (val > 9) val -= 9;
                    costs[i + inner_width * I][j + inner_width * J] = val;
                }
            }
        }
    }

    auto cmp = [](node left, node right) {return std::get<2>(left) > std::get<2>(right); };
    std::priority_queue<node, std::vector<node>, decltype(cmp)> PQ(cmp);
    PQ.emplace(0, 0, 0);
    totals[0][0] = 0;
    while (!PQ.empty())
    {
        node n = PQ.top();
        PQ.pop();
        uint16_t  i = std::get<0>(n);
        uint16_t  j = std::get<1>(n);
        uint16_t c = std::get<2>(n);
        if ((i == outer_width - 1) && (j == outer_width - 1))
            break;

        if (visited[i][j])
            continue;
        visited[i][j] = true;

        if (i > 0)
        {
            uint16_t new_c = c + costs[i - 1][j];
            if (new_c < totals[i - 1][j])
            {
                totals[i - 1][j] = new_c;
                PQ.emplace(i - 1, j, new_c);
            }
        }
        if (i < outer_width - 1)
        {
            uint16_t new_c = c + costs[i + 1][j];
            if (new_c < totals[i + 1][j])
            {
                totals[i + 1][j] = new_c;
                PQ.emplace(i + 1, j, new_c);
            }
        }
        if (j > 0)
        {
            uint16_t new_c = c + costs[i][j - 1];
            if (new_c < totals[i][j - 1])
            {
                totals[i][j - 1] = new_c;
                PQ.emplace(i, j - 1, new_c);
            }
        }
        if (j < outer_width - 1)
        {
            uint16_t new_c = c + costs[i][j + 1];
            if (new_c < totals[i][j + 1])
            {
                totals[i][j + 1] = new_c;
                PQ.emplace(i, j + 1, new_c);
            }
        }
    }
    std::cout << totals[outer_width - 1][outer_width - 1] << std::endl;

    // Test output
    /*std::cout << std::endl;
    for (size_t i = 0; i < outer_width; i++)
    {
        for (size_t j = 0; j < outer_width; j++)
            std::cout << (int)costs[i][j];
        std::cout << std::endl;
    }

    std::cout << std::endl;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
            std::cout << (int)totals[i][j] % 10;
        std::cout << std::endl;
    }*/

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
