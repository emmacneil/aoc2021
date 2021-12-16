#include <chrono>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <string>
#include <sstream>
#include <stdio.h>

struct packet
{
    uint8_t version, type;
    virtual int add_versions() { return version; }
};

struct operator_packet : public packet
{
    uint16_t length;
    std::vector<packet*> sub_packets;
    int add_versions()
    {
        int ret = version;
        for (packet* p : sub_packets) ret += p->add_versions();
        return ret;
    }
};

struct literal_packet : public packet
{
    std::vector<uint8_t> digits;
};

int parse(packet* &p, std::istream& is);
template<typename T, size_t n> T pop_bits(std::istream& is);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    //std::stringstream hex_stream("8A004A801A8002F478");
    //std::stringstream hex_stream("620080001611562C8802118E34");
    //std::stringstream hex_stream("C0015000016115A2E0802F182340");
    //std::stringstream hex_stream("A0016C880162017C3686B18A3D4780");
    std::stringstream bit_stream;
    char ch;
    std::string line;
    std::cin >> line;
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
    int bits_read = parse(p, bit_stream);
    std::cout << "version = " << (int)p->version << ", type = " << (int)p->type << std::endl;
    std::cout << "bits_read = " << bits_read << std::endl;
    std::cout << "Version sum = " << p->add_versions() << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

int parse(packet* &p, std::istream& is)
{
    uint8_t vers = pop_bits<uint8_t, 3>(is);
    uint8_t type = pop_bits<uint8_t, 3>(is);
    int bits_read = 6;
    if (type == 4)
    {
        p = new literal_packet;
        p->version = vers;
        p->type = type;
        printf("literal: vers = %d, type = %d\n", (int)vers, (int)type);

        uint8_t prefix;
        do
        {
            prefix = pop_bits<uint8_t, 1>(is);
            ((literal_packet*)p)->digits.push_back(pop_bits<uint8_t, 4>(is));
            bits_read += 5;
        } while (prefix);
        /*if (bits_read % 4)
        {
            is.ignore(4 - bits_read);
            bits_read += 4 - bits_read;
        }*/
    }
    else
    {
        p = new operator_packet;
        p->version = vers;
        p->type = type;
        uint8_t length_type = pop_bits<uint8_t, 1>(is);
        if (length_type)
        {
            uint16_t length = pop_bits<uint16_t, 11>(is);
            printf("literal: vers = %d, type = %d, length = %d (items)\n", (int)vers, (int)type, (int)length);
            bits_read += 12;
            for (uint16_t i = 0; i < length; i++)
            {
                packet* q = nullptr;
                std::cout << "Recurse" << std::endl;
                bits_read += parse(q, is);
                std::cout << "Pop" << std::endl;
                ((operator_packet*)p)->sub_packets.push_back(q);
            }
        }
        else
        {
            uint16_t length = pop_bits<uint16_t, 15>(is);
            printf("literal: vers = %d, type = %d, length = %d (bits)\n", (int)vers, (int)type, (int)length);
            bits_read += 16 + length;
            while (length > 0)
            {
                packet* q = nullptr;
                std::cout << "Recurse" << std::endl;
                length -= parse(q, is);
                std::cout << "Pop" << std::endl;
                ((operator_packet*)p)->sub_packets.push_back(q);
            }
        }
    }
    return bits_read;
}

template<typename T, size_t n> T pop_bits(std::istream& is)
{
    T ret = 0;
    for (size_t i = 0; i < n; i++)
    {
        char ch;
        is >> ch;
        ret <<= 1;
        ret |= (ch == '0') ? 0 : 1;
    }
    return ret;
}