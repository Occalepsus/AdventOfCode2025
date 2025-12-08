#pragma once

#include "DayInterface.h"

class Day6 : public DayInterface
{
public:
	Day6();

	~Day6() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	char problemLinesCount{ 0 };

	std::vector<bool> operands{};

	void parseOperands();

	static bool registered;
};
