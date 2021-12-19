#include <assert.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

typedef std::tuple<int16_t, int16_t, int16_t> triple;

template <int16_t a00, int16_t a01, int16_t a02,
          int16_t a10, int16_t a11, int16_t a12,
          int16_t a20, int16_t a21, int16_t a22>
triple rotate(const triple &t);
typedef triple(*rotation)(const triple&);
//std::vector<std::function<triple(const triple&)>> rotations{
std::vector<rotation> rotations{
rotate< 1,0,0,0, 1,0,0,0, 1>,
rotate<-1,0,0,0,-1,0,0,0, 1>,
rotate<-1,0,0,0, 1,0,0,0,-1>,
rotate< 1,0,0,0,-1,0,0,0,-1>,

rotate<-1,0,0,0,0, 1,0, 1,0>,
rotate< 1,0,0,0,0,-1,0, 1,0>,
rotate< 1,0,0,0,0, 1,0,-1,0>,
rotate<-1,0,0,0,0,-1,0,-1,0>,

rotate<0,-1,0, 1,0,0,0,0, 1>,
rotate<0, 1,0,-1,0,0,0,0, 1>,
rotate<0, 1,0, 1,0,0,0,0,-1>,
rotate<0,-1,0,-1,0,0,0,0,-1>,

rotate<0, 1,0,0,0, 1, 1,0,0>,
rotate<0,-1,0,0,0,-1, 1,0,0>,
rotate<0,-1,0,0,0, 1,-1,0,0>,
rotate<0, 1,0,0,0,-1,-1,0,0>,

rotate<0,0, 1, 1,0,0,0, 1,0>,
rotate<0,0,-1,-1,0,0,0, 1,0>,
rotate<0,0,-1, 1,0,0,0,-1,0>,
rotate<0,0, 1,-1,0,0,0,-1,0>,

rotate<0,0,-1,0, 1,0, 1,0,0>,
rotate<0,0, 1,0,-1,0, 1,0,0>,
rotate<0,0, 1,0, 1,0,-1,0,0>,
rotate<0,0,-1,0,-1,0,-1,0,0>};



triple operator-(const triple &p, const triple &q);
std::optional<triple> compare_with_transform(const std::vector<triple> &solved, const std::vector<triple> &unsolved, triple(*T)(const triple&));

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

            int16_t x, y, z;
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
                std::optional<triple> t = compare_with_transform(*solved, *unsolved, r);
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

    std::set<triple> S;
    for (auto v : solved_scanners)
        S.insert(v.begin(), v.end());
    std::cout << S.size() << std::endl;

    // Stick all the points in a set and count the number of unique points.

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

std::optional<triple> compare_with_transform(const std::vector<triple> &solved, const std::vector<triple> &unsolved, triple(*T)(const triple&))
{
    using std::get;
    std::map<triple, int16_t> count;

    for (const triple &p : solved)
    {
        for (const triple &q : unsolved)
        {
            triple d = T(q) - p;
            int16_t c = ++count[d];
            if (c >= 12)
                return d;
        }
    }
    return {};
}

template <int16_t a00, int16_t a01, int16_t a02,
          int16_t a10, int16_t a11, int16_t a12,
          int16_t a20, int16_t a21, int16_t a22>
triple rotate(const triple &t)
{
    using std::get;
    return std::make_tuple(a00*get<0>(t) + a01*get<1>(t) + a02*get<2>(t),
                           a10*get<0>(t) + a11*get<1>(t) + a12*get<2>(t),
                           a20*get<0>(t) + a21*get<1>(t) + a22*get<2>(t));
}

triple operator-(const triple &p, const triple &q)
{
    using std::get;
    return std::make_tuple(get<0>(p) - get<0>(q), get<1>(p) - get<1>(q), get<2>(p) - get<2>(q));
}
