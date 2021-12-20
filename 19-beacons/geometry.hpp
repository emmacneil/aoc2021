#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <map>
#include <optional>
#include <tuple>
#include <vector>

typedef std::tuple<int16_t, int16_t, int16_t> triple;
typedef triple(*rotation)(const triple&);

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

int16_t norm(const triple &p)
{
    using std::get;
    return (get<0>(p) < 0 ? -get<0>(p) : get<0>(p))
         + (get<1>(p) < 0 ? -get<1>(p) : get<1>(p))
         + (get<2>(p) < 0 ? -get<2>(p) : get<2>(p));
}

triple operator-(const triple &p, const triple &q)
{
    using std::get;
    return std::make_tuple(get<0>(p) - get<0>(q), get<1>(p) - get<1>(q), get<2>(p) - get<2>(q));
}

// Returns the vector difference of the scanners S1 and S2, if an overlap is detected.
// If no overlap is detected, returns nothing.
std::optional<triple> get_translation(const std::vector<triple> &S1, const std::vector<triple> &S2, triple(*T)(const triple&))
{
    using std::get;
    std::map<triple, int16_t> count;

    // For every pair of points ...
    for (const triple &p : S1)
    {
        for (const triple &q : S2)
        {
            // Calculate the difference between the two points.
            triple d = T(q) - p;

            // If 12 pairs of points had the same difference, assume that this is the difference between the two scanners.
            if (++count[d] >= 12) return d;
        }
    }
    return {};
}

std::vector<rotation> rotations
{
    rotate< 1, 0, 0, 0, 1, 0, 0, 0, 1>,
    rotate<-1, 0, 0, 0,-1, 0, 0, 0, 1>,
    rotate<-1, 0, 0, 0, 1, 0, 0, 0,-1>,
    rotate< 1, 0, 0, 0,-1, 0, 0, 0,-1>,
    rotate<-1, 0, 0, 0, 0, 1, 0, 1, 0>,
    rotate< 1, 0, 0, 0, 0,-1, 0, 1, 0>,
    rotate< 1, 0, 0, 0, 0, 1, 0,-1, 0>,
    rotate<-1, 0, 0, 0, 0,-1, 0,-1, 0>,
    rotate< 0,-1, 0, 1, 0, 0, 0, 0, 1>,
    rotate< 0, 1, 0,-1, 0, 0, 0, 0, 1>,
    rotate< 0, 1, 0, 1, 0, 0, 0, 0,-1>,
    rotate< 0,-1, 0,-1, 0, 0, 0, 0,-1>,
    rotate< 0, 1, 0, 0, 0, 1, 1, 0, 0>,
    rotate< 0,-1, 0, 0, 0,-1, 1, 0, 0>,
    rotate< 0,-1, 0, 0, 0, 1,-1, 0, 0>,
    rotate< 0, 1, 0, 0, 0,-1,-1, 0, 0>,
    rotate< 0, 0, 1, 1, 0, 0, 0, 1, 0>,
    rotate< 0, 0,-1,-1, 0, 0, 0, 1, 0>,
    rotate< 0, 0,-1, 1, 0, 0, 0,-1, 0>,
    rotate< 0, 0, 1,-1, 0, 0, 0,-1, 0>,
    rotate< 0, 0,-1, 0, 1, 0, 1, 0, 0>,
    rotate< 0, 0, 1, 0,-1, 0, 1, 0, 0>,
    rotate< 0, 0, 1, 0, 1, 0,-1, 0, 0>,
    rotate< 0, 0,-1, 0,-1, 0,-1, 0, 0>
};

#endif
