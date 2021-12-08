#include <iostream>

int gcd(int a, int b)
{
    if (a < 0) return gcd(-a, b);
    if (b < 0) return gcd(a, -b);
    if (b == 0) return a;
    if (b > a) return gcd(b, a);
    return gcd(b, a % b);
}

struct line
{
    struct point
    {
        point(line *l, int t) : parent(l), x(l->x + t*l->dx), y(l->y + t*l->dy), t(t) {}
        point& operator++() {x += parent->dx; y += parent->dy; t++; return *this;}
        bool operator!=(point &q) {return (parent != q.parent) || (t != q.t);}
        point& operator*() {return *this;}
        friend std::ostream& operator<<(std::ostream& os, point& p) {return os << "(" << p.x << ", " << p.y << ")";}
        line *parent;
        int x, y, t;
    };

    line(int x1, int y1, int x2, int y2) : x(x1), y(y1)
    {
        max_t = gcd(x2 - x1, y2 - y1); // might mess up if the inputs are negative
        dx = (x2 - x1) / max_t;
        dy = (y2 - y1) / max_t;
    }
    point begin() {return point(this, 0);}
    point end() {return point(this, max_t + 1);}
    int x, y, dx, dy, max_t;
};
