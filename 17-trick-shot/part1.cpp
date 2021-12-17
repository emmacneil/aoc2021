#include <assert.h>
#include <chrono>
#include <iostream>
#include <string>

bool exists_x(int x_min, int x_max, int t_min, int t_max);
int pos_x(int dx, int t);
int pos_y(int dy, int t);
int solve(int x_min, int x_max, int y_min, int y_max);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int x_min, x_max, y_min, y_max;
    std::cin.ignore(15);
    std::cin >> x_min;
    std::cin.ignore(2);
    std::cin >> x_max;
    std::cin.ignore(4);
    std::cin >> y_min;
    std::cin.ignore(2);
    std::cin >> y_max;

    std::cout << solve(x_min, x_max, y_min, y_max) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

// Returns true if there is a value of dx that places the device's x-coordinate
// between x_min and x_max between some times t_min and t_max
bool exists_x(int x_min, int x_max, int t_min, int t_max)
{
    static int initial_dx = 0;
    while (pos_x(initial_dx, t_min) < x_min)
        initial_dx++;

    for (int t = t_min; t <= t_max; t++)
    {
        int dx = initial_dx;
        int x;
        do
        {
            x = pos_x(dx, t);
        } while (x < x_min);
        if (x <= x_max)
            return true;
    }

    return false;
}

// Returns the x-coordinate at time t given an initial velocity of dx.
int pos_x(int dx, int t)
{
    return (t > dx) ? (dx*(dx + 1)/2) : t*(2*dx - t + 1)/2;
}

// Returns the y-coordinate at time t given an initial velocity of dy.
int pos_y(int dy, int t)
{
    return t*(2*dy - t + 1) / 2;
}

int solve(int x_min, int x_max, int y_min, int y_max)
{
    assert(x_min <= x_max);
    assert(y_min <= y_max);
    assert(x_min > 0);
    assert(y_max < 0);

    for (int dy = -y_min; dy > 0; dy--)
    {
        double y_max_d = (double)y_max;
        double y_min_d = (double)y_min;
        double b = (double)dy + 0.5;
        
        int t0 = (int)ceil(b + sqrt(b * b - 2.0 * y_max_d));
        int t1 = (int)floor(b + sqrt(b * b - 2.0 * y_min_d));

        if (t0 > t1) continue;
        if (exists_x(x_min, x_max, t0, t1))
            return dy*(dy + 1) / 2;
    }
    return 0;
}