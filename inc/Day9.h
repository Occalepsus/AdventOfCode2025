#pragma once

#include "DayInterface.h"

class Day9 : public DayInterface
{
public:
	Day9();

	~Day9() override = default;

	size_t part1() override;

	size_t part2() override;

private:

	std::vector<Tile> parseInput() const;

	static bool registered;
};
