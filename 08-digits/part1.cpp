#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string s;
    int count = 0;

    // As long as there is input...
    while (std::cin >> s)
    {
        // Skip the vertical bar and everything to the left of it.
        for (int i = 0; i < 10; i++) std::cin >> s;

        // Get the output digits and count the occurences of 1, 4, 7, and 8.
        for (int i = 0; i < 4; i++)
        {
            std::cin >> s;
            size_t sz = s.size();
            if ((sz == 2) || (sz == 3) || (sz == 4) || (sz == 7))
                count++;
        }

    }

    // Output
    std::cout << count << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}