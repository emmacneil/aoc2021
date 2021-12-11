#include <iostream>

int main(int argc, char *argv[])
{
    int a, b, c = 0;

    std::cin >> a;

    // Read integers.
    // If an integer is larger than the previous, increment the counter.
    while (std::cin >> b)
    {
        if (b > a) c++;
        a = b;
    }

    std::cout << c << std::endl;

    return 0;
}
