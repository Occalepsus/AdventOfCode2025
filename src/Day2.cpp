#include "Day2.h"

#include "DayFactory.h"

#include <algorithm>
#include <iostream>
#include <unordered_set>

bool Day2::registered = []() {
	DayFactory::get().registerDay(2, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day2>();
		});
	return true;
}();

Day2::Day2()
	: DayInterface(2, true)
{}

size_t Day2::part1()
{
	size_t res{ 0 };

	parseRanges();

	std::ranges::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
		return a.start < b.start;
	});

	size_t cur{ 1 };
	size_t curDoubled{ 11 };

	for (auto rangeIt{ ranges.cbegin() }; rangeIt != ranges.cend(); ++rangeIt)
	{
		while (curDoubled < rangeIt->start)
		{
			cur++;
			curDoubled = Utilities::concatNumbers(cur, cur);
		}
		while (curDoubled <= rangeIt->end)
		{
			res += curDoubled;

			std::cout << curDoubled << "\n";
			cur++;
			curDoubled = Utilities::concatNumbers(cur, cur);
		}
	}

	return res;
}

size_t Day2::part2()
{
	size_t res{ 0 };

	parseRanges();

	std::ranges::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
		return a.start < b.start;
	});

	std::unordered_set<size_t> invalidIds{};

	for (auto rangeIt{ ranges.cbegin() }; rangeIt != ranges.cend(); ++rangeIt)
	{
		size_t cur{ 1 };
		size_t curConcat{ 11 };

		while (curConcat <= rangeIt->end)
		{
			while (curConcat <= rangeIt->end)
			{
				if (rangeIt->start <= curConcat && curConcat <= rangeIt->end)
				{
					invalidIds.insert(curConcat);
				}

				curConcat = Utilities::concatNumbers(curConcat, cur);
			}

			cur++;
			curConcat = Utilities::concatNumbers(cur, cur);
		}
	}

	for (size_t elt: invalidIds)
	{
		std::cout << elt << "\n";
		res += elt;
	}

	return res;
}

Day2::Range::Range(std::string_view rangeStr)
{
	size_t dashPos{ rangeStr.find('-') };
	start = std::stoull(std::string(rangeStr.substr(0, dashPos)));
	end = std::stoull(std::string(rangeStr.substr(dashPos + 1)));
}

void Day2::parseRanges()
{
	const std::string& line{ inputLines[0] };

	size_t rangeStart{ 0 };
	size_t rangeEnd{ line.find(',') };

	while (rangeEnd != std::string::npos)
	{
		ranges.emplace_back(std::string_view(line.data() + rangeStart, rangeEnd - rangeStart));
		rangeStart = rangeEnd + 1;
		rangeEnd = line.find(',', rangeStart);
	}

	ranges.emplace_back(std::string_view(line.data() + rangeStart, line.size() - rangeStart));
}