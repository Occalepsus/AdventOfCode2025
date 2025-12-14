#include "Day9.h"

#include "DayFactory.h"

bool Day9::registered = []() {
	DayFactory::get().registerDay(9, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day9>();
		});
	return true;
}();

Day9::Day9()
	: DayInterface(9, true)
{}

size_t Day9::part1()
{
	const auto tiles{ parseInput() };

	std::vector<Tile>::const_iterator largestAIt;
	std::vector<Tile>::const_iterator largestBIt;
	size_t maxArea{ 0 };

	for (auto itA{ tiles.cbegin() }; itA != tiles.cend(); ++itA)
	{
		for (auto itB{ std::next(itA) }; itB != tiles.cend(); ++itB)
		{
			const size_t area{ ((*itB - *itA).abs() + Tile(1, 1)).area()};
			if (area > maxArea)
			{
				maxArea = area;
				largestAIt = itA;
				largestBIt = itB;
			}
		}
	}

	return maxArea;
}

size_t Day9::part2()
{
	size_t res{ 0 };

	return res;
}

std::vector<Tile> Day9::parseInput() const
{
	std::vector<Tile> tiles{};
	tiles.reserve(inputLines.size());

	for
		(const auto& line : inputLines)
	{
		tiles.emplace_back(line);
	}

	return tiles;
}