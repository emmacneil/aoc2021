#include <algorithm>
#include <assert.h>
#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::set<char> sets[10];

void classify_fives(std::vector<std::string>& str);
void classify_sixes(std::vector<std::string>& str);
void reset();
bool set_if_unique(std::string& s);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int total = 0;

    // As long as there is input...
    while (std::cin.peek() != EOF)
    {
        reset();
        std::string s;
        std::vector<std::string> fives, sixes;
        
        // Get a string of characters
        // If the string has five or six characters, keep track of it for later.
        // Otherwise we can tell by the number of characters whether they represent a 1, 4, 7, or 8.
        for (int i = 0; i < 10; i++)
        {
            std::cin >> s;
            if (!set_if_unique(s))
            {
                if (s.size() == 5)
                {
                    fives.push_back(s);
                }
                else
                {
                    sixes.push_back(s);
                }
            }
        }

        // Now that we have read in all the strings,
        // we can deduce which 5- and 6-long strings correspond to which digits.
        classify_fives(fives);
        classify_sixes(sixes);

        // Ignore ' |'
        std::cin.ignore(2);

        // Now read in the four output digits and determine which 4-digit number they represent.
        int result = 0;
        for (int i = 0; i < 4; i++)
        {
            std::cin >> s;
            std::set<char> output(s.begin(), s.end());
            for (int i = 0; i < 10; i++)
            {
                if (output == sets[i])
                {
                    result = result * 10 + i;
                    break;
                }
            }
        }
        total += result;
    }

    // Output
    std::cout << total << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

void classify_fives(std::vector<std::string>& str)
{
    assert(str.size() == 3);

    for (int i = 0; i < 3; i++)
    {
        std::set<char> s(str[i].begin(), str[i].end());

        // s represents either a 2, 3, or 5.

        // The segments of 1 are a subset of the segments of 3 (but not 2 or 5).
        if (std::includes(s.begin(), s.end(), sets[1].begin(), sets[1].end()))
        {
            sets[3].insert(s.begin(), s.end());
            continue;
        }

        // Adding the segments of 4 to 2 (but not to 5) gives 8.
        std::set<char> t(s);
        t.insert(sets[4].begin(), sets[4].end());
        if (std::includes(t.begin(), t.end(), sets[8].begin(), sets[8].end()))
            sets[2].insert(s.begin(), s.end());
        else
            sets[5].insert(s.begin(), s.end());
    }
}

void classify_sixes(std::vector<std::string>& str)
{
    assert(str.size() == 3);
    for (int i = 0; i < 3; i++)
    {
        std::set<char> s(str[i].begin(), str[i].end());

        // s represents either a 6, 9, or 0.

        // The segments of 4 are a subset of the segments of 9 (but not 6 or 0).
        if (std::includes(s.begin(), s.end(), sets[4].begin(), sets[4].end()))
        {
            sets[9].insert(s.begin(), s.end());
            continue;
        }

        // Adding the segments of 1 to 6 (but not to 0) gives 8.
        std::set<char> t(s);
        t.insert(sets[1].begin(), sets[1].end());
        if (std::includes(t.begin(), t.end(), sets[8].begin(), sets[8].end()))
            sets[6].insert(s.begin(), s.end());
        else
            sets[0].insert(s.begin(), s.end());
    }
}

void reset()
{
    for (int i = 0; i < 10; i++) sets[i].clear();
}

bool set_if_unique(std::string& s)
{
    if (s.size() == 2)
        sets[1].insert(s.begin(), s.end());
    else if (s.size() == 3)
        sets[7].insert(s.begin(), s.end());
    else if (s.size() == 4)
        sets[4].insert(s.begin(), s.end());
    else if (s.size() == 7)
        sets[8].insert(s.begin(), s.end());
    else
        return false;
    return true;
}

