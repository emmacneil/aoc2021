#include <chrono>
#include <iostream>
#include <list>
#include <stdint.h>
#include <string>

enum filter_t {O2, CO2};

uint64_t filter(const std::list<uint64_t> &numbers, int n_bits, filter_t mode);
uint64_t to_int(const std::string &s);

int main(int argc, char *argv[])
{
	std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

	std::string bit_string;
	std::list<uint64_t> numbers;
	int n_numbers = 0;

	// Read first line to determine number of bits per line
	std::cin >> bit_string;
	int n_bits = bit_string.size();
	int common[n_bits] = {0}; // array to count number of times 1 appears in each bit position
	do
	{
		n_numbers++;
		uint64_t n = 0;
		numbers.push_back(to_int(bit_string));
		for (int i = 0; i < n_bits; i++)
		{
			char ch = bit_string.at(i);
			n <<= 1;
			if (ch - '0')
			{
				n |= 1;
				common[i]++;
			}
		}
	} while (std::cin >> bit_string);

	uint64_t o2  = filter(numbers, n_bits, O2);
	uint64_t co2 = filter(numbers, n_bits, CO2);
	std::cout << o2*co2 << std::endl;

	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

	return 0;
}

uint64_t filter(const std::list<uint64_t> &numbers, int n_bits, filter_t mode)
{
	uint64_t mask = 1ULL << (n_bits - 1);
	std::list<uint64_t> l(numbers.begin(), numbers.end());

	while (l.size() > 1)
	{
		size_t n_numbers = l.size();

		// Find number of numbers with a 1 in the first position
		size_t count = 0;
		for (uint64_t n : l) if (n & mask) count++;
		uint64_t common = (mode == O2)
		                ? (count + count <  n_numbers ? 0 : mask)
						: (count + count >= n_numbers ? 0 : mask);

		auto it = l.begin();
		while (l.size() > 1 && it != l.end())
		{
			if (((*it) & mask) == common)
				it++;
			else
				l.erase(it++);
		}
		mask >>= 1;
	}

	return l.front();
}

uint64_t to_int(const std::string &s)
{
	uint64_t ret = 0;
	for (char ch : s)
	{
		ret <<= 1;
		ret |= (uint64_t)(ch - '0');
	}
	return ret;
}
