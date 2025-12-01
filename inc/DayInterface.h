#pragma once

#include "Utilities.h"

#include <vector>
#include <string>
#include <format>

class DayInterface
{
public:
	const int dayNumber{ 0 };

	explicit DayInterface(int dayNumber, bool fromUrl = true)
		: dayNumber(dayNumber)
		, inputLines(fromUrl ? Utilities::getUrlContent(Utilities::getCookieFromFile("../../aoc_cookie.txt"), std::format("https://adventofcode.com/2025/day/{}/input", dayNumber)) : Utilities::getPromptContent())
	{};

	virtual ~DayInterface() = default;

	virtual size_t part1() = 0;

	virtual size_t part2() = 0;

protected:
	std::vector<std::string> inputLines{};
};