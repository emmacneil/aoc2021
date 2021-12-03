#include <iostream>
#include <stdint.h>
#include <string>

int main(int argc, char *argv[])
{
	std::string bit_string;

	// Read first line to determine number of bits per line
	std::cin >> bit_string;
	int n_bits = bit_string.size();
	int ones[n_bits] = {0};
	
	// Count the number of 1's in each position across all lines
	int n_lines = 0;
	do
	{
		for (int i = 0; i < n_bits; i++)
			ones[i] += bit_string.at(i) == '1' ? 1 : 0;
		n_lines++;
	} while (std::cin >> bit_string);

	// Construct gamma and epsilon.
	// Epsilon is calculated as the bitwise NOT of gamma.
	uint64_t gamma = 0;
	for (int i = 0; i < n_bits; i++)
		gamma = (gamma << 1) ^ (ones[i] > n_lines / 2 ? 1 : 0);
	uint64_t mask = (1 << n_bits) - 1;
	uint64_t epsilon = ~gamma & mask;
	
	std::cout << gamma*epsilon << std::endl;

	return 0;
}
