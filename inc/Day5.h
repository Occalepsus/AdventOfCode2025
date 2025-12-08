#pragma once

#include "DayInterface.h"

#include <list>

class Day5 : public DayInterface
{
public:
	Day5();

	~Day5() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::list<Utilities::Range> ranges{};

	std::vector<uint64_t> ingredientIds{};

	void parseInput();

	static bool registered;
};
