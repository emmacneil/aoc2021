#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string s;
	int n, depth = 0, horizontal = 0;	

	while (std::cin >> s >> n)
	{
		switch (s.at(0))
		{
		case 'd': // down
			depth += n;
			break;
		case 'f': // forward
			horizontal += n;
			break;
		case 'u': // up
			depth -= n;
			break;
		}
	}

	std::cout << horizontal*depth << std::endl;
	
	return 0;
}
