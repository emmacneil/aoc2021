CFLAGS = -std=c++17 -O3

all : part1 part2

part1 : part1.cpp geometry.hpp
	g++ -o part1 $(CFLAGS) part1.cpp

part2 : part2.cpp geometry.hpp
	g++ -o part2 $(CFLAGS) part2.cpp

clean :
	@rm -f part1 part2
