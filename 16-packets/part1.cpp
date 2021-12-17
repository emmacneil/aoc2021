#include "packet.hpp"

#include <chrono>
#include <stdint.h>
#include <string>
#include <sstream>

uint32_t solve(std::string& line)
{
    std::stringstream bit_stream;
    char ch;

    for (char ch : line)
    {
        switch (ch)
        {
        case '0': bit_stream << "0000"; break;
        case '1': bit_stream << "0001"; break;
        case '2': bit_stream << "0010"; break;
        case '3': bit_stream << "0011"; break;
        case '4': bit_stream << "0100"; break;
        case '5': bit_stream << "0101"; break;
        case '6': bit_stream << "0110"; break;
        case '7': bit_stream << "0111"; break;
        case '8': bit_stream << "1000"; break;
        case '9': bit_stream << "1001"; break;
        case 'A': bit_stream << "1010"; break;
        case 'B': bit_stream << "1011"; break;
        case 'C': bit_stream << "1100"; break;
        case 'D': bit_stream << "1101"; break;
        case 'E': bit_stream << "1110"; break;
        case 'F': bit_stream << "1111"; break;
        }
    }

    packet* p = nullptr;
    packet::parse(p, bit_stream);
    uint32_t ret = p->add_versions();

    delete p;
    return ret;
}

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line;
    while (std::cin >> line)
    {
        std::cout << solve(line) << std::endl;
    }

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
