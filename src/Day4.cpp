#include "Day4.h"

#include "DayFactory.h"

#include <iostream>
#include <array>
#include <algorithm>

namespace
{
	constexpr std::array<std::pair<int16_t, int16_t>, 8> directions{
		std::make_pair(-1, -1),
		std::make_pair(-1, 0),
		std::make_pair(-1, 1),
		std::make_pair(0, -1),
		std::make_pair(0, 1),
		std::make_pair(1, -1),
		std::make_pair(1, 0),
		std::make_pair(1, 1)
	};
}

bool Day4::registered = []() {
	DayFactory::get().registerDay(4, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day4>();
		});
	return true;
}();

Day4::Day4()
	: DayInterface(4, true)
{}

size_t Day4::part1()
{
	parseInput();

	return liftPossibleRolls();
}

size_t Day4::part2()
{
	parseInput();

	size_t res{ 0 };

	size_t lifted{ 0 };
	do
	{
		lifted = liftPossibleRolls(false);

		std::cout << "Lifted rolls this iteration: " << lifted << '\n';
		res += lifted;

		std::ranges::for_each(floorTiles.begin(), floorTiles.end(), [](FloorTile& curTile)
		{
			if (curTile == FloorTile::LifedRoll)
			{
				curTile = FloorTile::Empty;
			}
		});
	}
	while (lifted > 0);

	return res;
}

void Day4::parseInput()
{
	width = static_cast<int16_t>(inputLines[0].size() + 2);
	height = static_cast<int16_t>(inputLines.size() + 2);

	floorTiles.resize(static_cast<size_t>(width) * static_cast<size_t>(height), FloorTile::Empty);

	for (int16_t y = 0; y < static_cast<int16_t>(inputLines.size()); ++y)
	{
		for (int16_t x = 0; x < static_cast<int16_t>(inputLines[y].size()); ++x)
		{
			if (inputLines[y][x] == '@')
			{
				floorTiles[static_cast<size_t>((y + 1) * width) + x + 1] = FloorTile::Roll;
			}
		}
	}
}

Day4::FloorTile Day4::getTileAt(int16_t x, int16_t y)
{
	return floorTiles[static_cast<size_t>(y * width) + x];
}

void Day4::setTileAt(int16_t x, int16_t y, FloorTile tile)
{
	floorTiles[static_cast<size_t>(y * width) + x] = tile;
}

size_t Day4::liftPossibleRolls(bool verbose)
{
	size_t res{ 0 };

	for (int16_t y = 1; y < height - 1; ++y)
	{
		for (int16_t x = 1; x < width - 1; ++x)
		{
			if (getTileAt(x, y) != FloorTile::Roll)
			{
				verbose && std::cout << '.';
			}
			else if (countAround(x, y, 4) < 4)
			{
				verbose && std::cout << 'x';
				++res;
				setTileAt(x, y, FloorTile::LifedRoll);
			}
			else
			{
				verbose && std::cout << '@';
			}
		}
		verbose && std::cout << '\n';
	}

	return res;
}

int Day4::countAround(int16_t x, int16_t y, int lazyLimit)
{
	int count{ 0 };

	for (const auto& [dx, dy] : directions)
	{
		// Early exit if we already have 4 adjacent rolls
		if (getTileAt(x + dx, y + dy) != FloorTile::Empty)
		{
			++count;
			if (count >= lazyLimit)
			{
				break;
			}
		}
	}

	return count;
}