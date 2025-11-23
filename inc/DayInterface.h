#pragma once

#include "Utilities.h"

#include <vector>
#include <string>
#include <format>

class DayInterface
{
public:
	const int dayNumber{ 0 };

	explicit DayInterface(int dayNumber)
		: dayNumber(dayNumber)
		, inputLines(Utilities::getUrlContent(Utilities::getCookieFromFile("../../aoc_cookie.txt"), std::format("https://adventofcode.com/2024/day/{}/input", dayNumber)))
	{};

	virtual ~DayInterface() = default;

	virtual size_t part1() = 0;

	virtual size_t part2() = 0;

protected:
	std::vector<std::string> inputLines{};
};