#pragma once

#include "DayInterface.h"

class Day2 : public DayInterface
{
public:
	Day2();

	~Day2() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	struct Range
	{
		size_t start{ 0 };

		size_t end{ 0 };

		Range(size_t s, size_t e) : start(s), end(e) {};

		explicit Range(std::string_view rangeStr);
	};

	std::vector<Range> ranges{};

	void parseRanges();

	static bool registered;
};
