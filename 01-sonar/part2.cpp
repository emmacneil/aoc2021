#include <iostream>

int main(int argc, char *argv[])
{
    int a1, a2, a3, b, c = 0;

    std::cin >> a1 >> a2 >> a3;

    // Read integers.
    // If an integer is larger than the one three integers ago, increment the counter.
    while (std::cin >> b)
    {
        if (b > a1) c++;
        a1 = a2;
        a2 = a3;
        a3 = b;
    }

    std::cout << c << std::endl;

    return 0;
}
