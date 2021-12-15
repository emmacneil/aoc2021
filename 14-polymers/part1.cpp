#include <chrono>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    uint64_t bigraphs[2][26][26] = { 0 };
    char rules[26][26] = { 0 };
    uint64_t count[26] = { 0 };
    std::string line;
    const int N_ROUNDS = 10;
    char first_ch;

    // Get starting string
    std::cin >> line;
    for (size_t i = 0; i < line.size() - 1; i++)
        bigraphs[0][line[i] - 'A'][line[i+1] - 'A']++;
    first_ch = line[0];
    getline(std::cin, line); // ignore an empty line.

    // Get replacement rules
    while (!std::cin.eof())
    {
        char a, b, c;
        std::cin >> a >> b;
        std::cin.ignore(4); // ignore " -> "
        std::cin >> c;
        rules[a - 'A'][b - 'A'] = c;
    }

    size_t curr = 1, last = 0;
    for (size_t r = 0; r < N_ROUNDS; r++)
    {
        memset(bigraphs[curr], 0, 26 * 26 * sizeof(uint64_t));
        for (size_t i = 0; i < 26; i++)
        {
            for (size_t j = 0; j < 26; j++)
            {
                bigraphs[curr][i][rules[i][j] - 'A'] += bigraphs[last][i][j];
                bigraphs[curr][rules[i][j] - 'A'][j] += bigraphs[last][i][j];
                // ...
            }
        }
        curr ^= 1;
        last ^= 1;
    }

    count[first_ch - 'A'] = 1;
    for (size_t i = 0; i < 26; i++)
        for (size_t j = 0; j < 26; j++)
            count[j] += bigraphs[last][i][j];

    uint64_t m = std::numeric_limits<uint64_t>::max(), M = 0;
    for (size_t i = 0; i < 26; i++)
    {
        if (count[i])
        {
            m = count[i] < m ? count[i] : m;
            M = count[i] > M ? count[i] : M;
        }
    }
    std::cout << M - m << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
