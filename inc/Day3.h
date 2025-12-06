#pragma once

#include "DayInterface.h"

class Day3 : public DayInterface
{
public:
	Day3();

	~Day3() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<std::vector<int8_t>> batteries{};

	void parseInput();


	static bool registered;
};
