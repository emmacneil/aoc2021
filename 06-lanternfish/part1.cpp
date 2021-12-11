#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    // arr[n] will contain the number of fish with n days left on their internal timer
    int arr[9] = {0};
    int n_days = 80;

    // Get the input.
    // The input is a single line of numbers separated by commas.
    // Each number is one digit.
    char c;
    std::cin >> c;
    arr[c - '0']++;
    while (std::cin >> c)
    {
        std::cin >> c;
        arr[c - '0']++;
    }

    // Simulate the fish breeding
    for (int d = 0; d < n_days; d++)
    {
        int tmp = arr[0];
        arr[0] = arr[1];
        arr[1] = arr[2];
        arr[2] = arr[3];
        arr[3] = arr[4];
        arr[4] = arr[5];
        arr[5] = arr[6];
        arr[6] = tmp + arr[7];
        arr[7] = arr[8];
        arr[8] = tmp;
    }

    // Count the fishies
    int total = 0;
    for (int i = 0; i < 9; i++)
        total += arr[i];

    // Output
    std::cout << total << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;
	
	return 0;
}