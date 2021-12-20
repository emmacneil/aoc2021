CFLAGS = -std=c++11 -O3

all : part1 part2

part1 : part1.cpp automata.hpp
	g++ -o part1 $(CFLAGS) part1.cpp

part2 : part2.cpp automata.hpp
	g++ -o part2 $(CFLAGS) part2.cpp

clean :
	@rm -f part1 part2