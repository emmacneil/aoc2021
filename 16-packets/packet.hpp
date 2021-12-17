#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <limits>
#include <stdint.h>
#include <vector>

struct packet
{
    virtual ~packet() {}
    virtual uint32_t add_versions() { return version; }
    virtual uint64_t evaluate() { return 0; }
    static uint32_t parse(packet* &p, std::istream& is);

    uint8_t version, type;
};

struct literal_packet : public packet
{
    uint64_t evaluate();

    std::vector<uint8_t> digits;
};

struct operator_packet : public packet
{
    ~operator_packet();
    uint32_t add_versions();
    uint64_t evaluate();

    uint16_t length;
    std::vector<packet*> sub_packets;
};

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

uint32_t packet::parse(packet* &p, std::istream& is)
{
    uint8_t vers = pop_bits<uint8_t, 3>(is);
    uint8_t type = pop_bits<uint8_t, 3>(is);
    uint32_t bits_read = 6;
    if (type == 4)
    {
        p = new literal_packet;
        p->version = vers;
        p->type = type;

        uint8_t prefix;
        do
        {
            prefix = pop_bits<uint8_t, 1>(is);
            ((literal_packet*)p)->digits.push_back(pop_bits<uint8_t, 4>(is));
            bits_read += 5;
        } while (prefix);
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
            bits_read += 12;
            for (uint16_t i = 0; i < length; i++)
            {
                packet* q = nullptr;
                bits_read += parse(q, is);
                ((operator_packet*)p)->sub_packets.push_back(q);
            }
        }
        else
        {
            uint16_t length = pop_bits<uint16_t, 15>(is);
            bits_read += 16 + length;
            while (length > 0)
            {
                packet* q = nullptr;
                length -= parse(q, is);
                ((operator_packet*)p)->sub_packets.push_back(q);
            }
        }
    }
    return bits_read;
}

uint64_t literal_packet::evaluate()
{
    uint64_t ret = 0;
    for (uint8_t digit : digits)
        ret = (ret << 4) ^ (uint64_t)digit;
    return ret;
}

operator_packet::~operator_packet()
{
    for (packet *p : sub_packets)
        delete p;
}

uint32_t operator_packet::add_versions()
{
    uint32_t ret = version;
    for (packet* p : sub_packets) ret += p->add_versions();
    return ret;
}

uint64_t operator_packet::evaluate()
{
    uint64_t ret;

    switch (type)
    {
    case 0: // sum
        ret = 0;
        for (packet *p : sub_packets) ret += p->evaluate();
        break;
    case 1: // product
        ret = 1;
        for (packet *p : sub_packets) ret *= p->evaluate();
        break;
    case 2: // minimum
        ret = std::numeric_limits<uint64_t>::max();
        for (packet *p : sub_packets)
        {
            uint64_t e = p->evaluate();
            ret = e < ret ? e : ret;
        }
        break;
    case 3: // maximum
        ret = std::numeric_limits<uint64_t>::min();
        for (packet *p : sub_packets)
        {
            uint64_t e = p->evaluate();
            ret = e > ret ? e : ret;
        }
        break;
    case 5: // greater-than
        ret = sub_packets[0]->evaluate() > sub_packets[1]->evaluate();
        break;
    case 6: // lesser-than
        ret = sub_packets[0]->evaluate() < sub_packets[1]->evaluate();
        break;
    case 7: // equal-to
        ret = sub_packets[0]->evaluate() == sub_packets[1]->evaluate();
        break;
    default:
        ret = 0;
    }
    return ret;
}

#endif
