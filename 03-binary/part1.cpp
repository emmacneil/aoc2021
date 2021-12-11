#include <chrono>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

	std::string bit_string;
	int n_numbers = 0;

	// Read first line to determine number of bits per line
	std::cin >> bit_string;
	std::vector<int> common(bit_string.size(), 0); // array to count number of times 1 appears in each bit position
	do
	{
		n_numbers++;
		for (int i = 0; i < bit_string.size(); i++)
			if (bit_string.at(i) - '0')
				common[i]++;
	} while (std::cin >> bit_string);

	uint64_t gamma = 0, epsilon = 0;
	for (int n : common)
	{
		gamma <<= 1;
		epsilon <<= 1;
		if (n > n_numbers / 2)
			gamma |= 1;
		else
			epsilon |= 1;
	}

	std::cout << epsilon*gamma << std::endl;

	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

	return 0;
}
