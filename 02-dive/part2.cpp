#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string s;
	int n, aim = 0, depth = 0, horizontal = 0;	

	while (std::cin >> s >> n)
	{
		switch (s.at(0))
		{
		case 'd': // down
			aim += n;
			break;
		case 'f': // forward
			horizontal += n;
			depth += n*aim;
			break;
		case 'u': // up
			aim -= n;
			break;
		}
	}

	// This is dangerously close to an overflow on the problem input.
	std::cout << horizontal*depth << std::endl;
	
	return 0;
}
