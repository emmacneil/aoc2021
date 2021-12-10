#include <algorithm>
#include <chrono>
#include <iostream>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

bool handle_char(std::stack<char> &S, char ch);
uint64_t score(std::stack<char>& S);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::vector<uint64_t> scores;

    // Fetch input
    std::string str;
    while (std::cin >> str)
    {
        std::stack<char> S;
        bool corrupted = false;
        for (char ch : str)
        {
            corrupted = handle_char(S, ch);
            if (corrupted)
                break;
        }

        if (corrupted)
            continue;

        // Line is considered incomplete at this point. Determine score
        scores.push_back(score(S));
    }

    std::sort(scores.begin(), scores.end());
    std::cout << scores[scores.size()/2] << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

bool handle_char(std::stack<char> &S, char ch)
{
    switch (ch)
    {
    case ')':
        if (S.top() == '(') S.pop();
        else return true;
        break;
    case ']':
        if (S.top() == '[') S.pop();
        else return true;
        break;
    case '}':
        if (S.top() == '{') S.pop();
        else return true;
        break;
    case '>':
        if (S.top() == '<') S.pop();
        else return true;
        break;
    default:
        S.push(ch);
        break;
    }
    return false;
}

uint64_t score(std::stack<char>& S)
{
    uint64_t ret = 0ULL;
    while (!S.empty())
    {
        ret *= 5ULL;
        switch (S.top())
        {
        case '(':
            ret += 1ULL;
            break;
        case '[':
            ret += 2ULL;
            break;
        case '{':
            ret += 3ULL;
            break;
        case '<':
            ret += 4ULL;
            break;
        }
        S.pop();
    }
    return ret;
}