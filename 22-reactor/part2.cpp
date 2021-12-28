#include <assert.h>
#include <chrono>
#include <iostream>
#include <list>
#include <string>

struct box
{
    box() : x1(0), y1(0), z1(0), x2(0), y2(0), z2(0) {}
    box(int x1, int y1, int z1, int x2, int y2, int z2)
        : x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2) {}
    int x1, y1, z1, x2, y2, z2;
    bool contains(const box& other) const;
    bool intersects(const box& other) const;
    long long volume() const;
};

struct boxset
{
    std::list<box> l;
    void add(const box& b);
    void remove(const box& b);
    long long volume() const;
};

int main(int argc, char* argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    boxset bs;
    std::string on_off;
    while (std::cin >> on_off)
    {
        box b;
        std::cin.ignore(3); // Ignore " x="
        std::cin >> b.x1;
        std::cin.ignore(2); // "Ignore ".."
        std::cin >> b.x2;
        std::cin.ignore(3); // "Ignore ",y="
        std::cin >> b.y1;
        std::cin.ignore(2); // "Ignore ".."
        std::cin >> b.y2;
        std::cin.ignore(3); // "Ignore ",z="
        std::cin >> b.z1;
        std::cin.ignore(2); // "Ignore ".."
        std::cin >> b.z2;

        assert(b.x1 <= b.x2);
        assert(b.y1 <= b.y2);
        assert(b.z1 <= b.z2);

        if (on_off == "on")
            bs.add(b);
        else
            bs.remove(b);
    }

    std::cout << bs.volume() << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

bool box::contains(const box& other) const
{
    return (x1 <= other.x1) && (other.x2 <= x2) && (y1 <= other.y1) && (other.y2 <= y2) && (z1 <= other.z1) && (other.z2 <= z2);
}

bool box::intersects(const box& other) const
{
    return (x1 <= other.x2) && (other.x1 <= x2) && (y1 <= other.y2) && (other.y1 <= y2) && (z1 <= other.z2) && (other.z1 <= z2);
}

long long box::volume() const
{
    using ll = long long;
    return (ll(x2) - ll(x1) + 1LL)* (ll(y2) - ll(y1) + 1LL)* (ll(z2) - ll(z1) + 1LL);
}

void boxset::add(const box& b)
{
    for (const auto& B : l)
    {
        if (b.intersects(B))
        {
            if (b.x1 < B.x1)
            {
                add(box(b.x1, b.y1, b.z1, B.x1 - 1, b.y2, b.z2));
                add(box(B.x1, b.y1, b.z1, b.x2, b.y2, b.z2));
            }
            else if (B.x2 < b.x2)
            {
                add(box(b.x1, b.y1, b.z1, B.x2, b.y2, b.z2));
                add(box(B.x2 + 1, b.y1, b.z1, b.x2, b.y2, b.z2));
            }
            else if (b.y1 < B.y1)
            {
                add(box(b.x1, b.y1, b.z1, b.x2, B.y1 - 1, b.z2));
                add(box(b.x1, B.y1, b.z1, b.x2, b.y2, b.z2));
            }
            else if (B.y2 < b.y2)
            {
                add(box(b.x1, b.y1, b.z1, b.x2, B.y2, b.z2));
                add(box(b.x1, B.y2 + 1, b.z1, b.x2, b.y2, b.z2));
            }
            else if (b.z1 < B.z1)
            {
                add(box(b.x1, b.y1, b.z1, b.x2, b.y2, B.z1 - 1));
                add(box(b.x1, b.y1, B.z1, b.x2, b.y2, b.z2));
            }
            else if (B.z2 < b.z2)
            {
                add(box(b.x1, b.y1, b.z1, b.x2, b.y2, B.z2));
                add(box(b.x1, b.y1, B.z2 + 1, b.x2, b.y2, b.z2));
            }
            return;
        }
    }
    l.push_back(b);
}

void boxset::remove(const box& b)
{
    auto it = l.begin();
    while (it != l.end())
    {
        if (b.contains(*it))
            it = l.erase(it);
        else if (b.intersects(*it))
        {
            if (it->x1 < b.x1)
            {
                l.emplace_back(it->x1, it->y1, it->z1, b.x1 - 1, it->y2, it->z2);
                l.emplace_back(b.x1, it->y1, it->z1, it->x2, it->y2, it->z2);
            }
            else if (b.x2 < it->x2)
            {
                l.emplace_back(it->x1, it->y1, it->z1, b.x2, it->y2, it->z2);
                l.emplace_back(b.x2 + 1, it->y1, it->z1, it->x2, it->y2, it->z2);
            }
            else if (it->y1 < b.y1)
            {
                l.emplace_back(it->x1, it->y1, it->z1, it->x2, b.y1 - 1, it->z2);
                l.emplace_back(it->x1, b.y1, it->z1, it->x2, it->y2, it->z2);
            }
            else if (b.y2 < it->y2)
            {
                l.emplace_back(it->x1, it->y1, it->z1, it->x2, b.y2, it->z2);
                l.emplace_back(it->x1, b.y2 + 1, it->z1, it->x2, it->y2, it->z2);
            }
            else if (it->z1 < b.z1)
            {
                l.emplace_back(it->x1, it->y1, it->z1, it->x2, it->y2, b.z1 - 1);
                l.emplace_back(it->x1, it->y1, b.z1, it->x2, it->y2, it->z2);
            }
            else if (b.z2 < it->z2)
            {
                l.emplace_back(it->x1, it->y1, it->z1, it->x2, it->y2, b.z2);
                l.emplace_back(it->x1, it->y1, b.z2 + 1, it->x2, it->y2, it->z2);
            }
            it = l.erase(it);
        }
        else
            ++it;
    }
}

long long boxset::volume() const
{
    long long ret = 0;
    for (const auto& b : l)
        ret += b.volume();
    return ret;
}