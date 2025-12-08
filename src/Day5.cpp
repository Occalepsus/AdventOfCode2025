#include "Day5.h"

#include "DayFactory.h"

#include <algorithm>

bool Day5::registered = []() {
	DayFactory::get().registerDay(5, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day5>();
		});
	return true;
}();

Day5::Day5()
	: DayInterface(5, true)
{
	parseInput();
}

size_t Day5::part1()
{
	size_t res{ 0 };

	auto rangeIt{ ranges.cbegin() };
	for (const uint64_t id : ingredientIds)
	{
		while (rangeIt != ranges.cend() && rangeIt->end < id)
		{
			++rangeIt;
		}

		if (rangeIt == ranges.cend())
		{
			break;
		}

		if (rangeIt->start <= id && id <= rangeIt->end)
		{
			++res;
			continue;
		}
	}


	return res;
}

size_t Day5::part2()
{
	size_t res{ 0 };

	for (const auto& range : ranges)
	{
		res += (range.end - range.start + 1);
	}

	return res;
}



void Day5::parseInput()
{
	bool ingredientSection{ false };

	for (const std::string& line : inputLines)
	{
		if (line.empty())
		{
			ingredientSection = true;
			continue;
		}
		if (ingredientSection)
		{
			ingredientIds.push_back(std::stoull(line));
		}
		else
		{
			ranges.emplace_back(line);
		}
	}

	ranges.sort([](const Utilities::Range& a, const Utilities::Range& b) {
		return a.start < b.start;
	});

	for (auto it1 = ranges.begin(); it1 != ranges.end(); ++it1)
	{
		auto it2{ it1 };
		++it2;
		while (it2 != ranges.end())
		{
			if (it1->tryMerge(*it2))
			{
				it2 = ranges.erase(it2);
			}
			else
			{
				++it2;
			}
		}
	}

	std::ranges::sort(ingredientIds);
}


/*
>719
=737
*/