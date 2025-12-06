#include "Day3.h"

#include "DayFactory.h"

#include <algorithm>
#include <iostream>

bool Day3::registered = []() {
	DayFactory::get().registerDay(3, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day3>();
		});
	return true;
}();

Day3::Day3()
	: DayInterface(3, true)
{
	parseInput();
}

size_t Day3::part1()
{
	size_t res{ 0 };

	for (const auto& battery : batteries)
	{
		// Look for the max element except the last one (the tens digit cannot be the last one)
		auto tensIt{ std::ranges::max_element(battery.cbegin(), battery.cend() - 1) };

		// Look for the max element in the remaining part (after the tens digit)
		auto unitsIt{ std::ranges::max_element(tensIt + 1, battery.cend()) };

		res += static_cast<size_t>((*tensIt) * 10 + (*unitsIt));
	}

	return res;
}

size_t Day3::part2()
{
	size_t res{ 0 };

	for (const auto& battery : batteries)
	{
		int64_t batteryValue{ 0 };
		auto digitIt{ battery.cbegin() };

		for (int digitId{ 11 }; digitId >= 0; --digitId)
		{
			digitIt = std::ranges::max_element(digitIt, battery.cend() - digitId);

			batteryValue = batteryValue * 10 + *digitIt;

			digitIt++;
		}

		//std::cout << "Battery value: " << batteryValue << "\n";

		res += static_cast<size_t>(batteryValue);
	}

	return res;
}

void Day3::parseInput()
{
	batteries.clear();

	for (const auto& battery : inputLines)
	{
		std::vector<int8_t> batteryLevels;
		for (const char c : battery)
		{
			batteryLevels.push_back(static_cast<int8_t>(c - '0'));
		}
		batteries.push_back(batteryLevels);
	}
}