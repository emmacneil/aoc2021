#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include <iostream>
#include <vector>

int count_cells(const std::vector<std::vector<bool>>& cells)
{
	int ret = 0;
	for (const auto& row : cells)
		for (bool b : row)
			if (b) ret++;
	return ret;
}

int fetch(const std::vector<std::vector<bool>>& cells, const std::vector<bool>& rules, int i, int j, int round)
{
	if (i < 0 || j < 0 || i >= cells.size() || j >= cells.size())
	{
		if (rules[0])
			return (round & 1) ? rules.back() : rules.front();
		return 0;
	}
	return cells[i][j];
}

void print_grid(const std::vector<std::vector<bool>>& cells)
{
	for (const auto& row : cells)
	{
		for (bool b : row)
			std::cout << (char)(b ? '#' : '.');
		std::cout << std::endl;
	}
}

void sim(std::vector<std::vector<bool>> &cells, const std::vector<bool> &rules, int round)
{
	std::vector<std::vector<bool>> new_cells(cells.size() + 2, std::vector<bool>(cells.size() + 2, false));
	size_t w = new_cells.size();
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int k = 0;
			k = (k << 1) ^ fetch(cells, rules, i - 2, j - 2, round);
			k = (k << 1) ^ fetch(cells, rules, i - 2, j - 1, round);
			k = (k << 1) ^ fetch(cells, rules, i - 2, j - 0, round);
			k = (k << 1) ^ fetch(cells, rules, i - 1, j - 2, round);
			k = (k << 1) ^ fetch(cells, rules, i - 1, j - 1, round);
			k = (k << 1) ^ fetch(cells, rules, i - 1, j - 0, round);
			k = (k << 1) ^ fetch(cells, rules, i - 0, j - 2, round);
			k = (k << 1) ^ fetch(cells, rules, i - 0, j - 1, round);
			k = (k << 1) ^ fetch(cells, rules, i - 0, j - 0, round);
			new_cells[i][j] = rules[k];
		}
	}
	cells = new_cells;
}

#endif