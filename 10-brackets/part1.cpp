#include <chrono>
#include <iostream>
#include <stack>
#include <string>

int handle_char(std::stack<char> &S, char ch);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int points = 0;

    // Fetch input
    std::string str;
    while (std::cin >> str)
    {
        std::stack<char> S;
        for (char ch : str)
        {
            int result = handle_char(S, ch);
            points += result;
            if (result)
                break;
        }
    }

    std::cout << points << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

int handle_char(std::stack<char> &S, char ch)
{
    switch (ch)
    {
    case ')':
        if (S.top() == '(') S.pop();
        else return 3;
        break;
    case ']':
        if (S.top() == '[') S.pop();
        else return 57;
        break;
    case '}':
        if (S.top() == '{') S.pop();
        else return 1197;
        break;
    case '>':
        if (S.top() == '<') S.pop();
        else return 25137;
        break;
    default:
        S.push(ch);
        break;
    }
    return 0;
}
