#pragma once

#include "DayInterface.h"

class Day4 : public DayInterface
{
public:
	Day4();

	~Day4() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	enum class FloorTile : uint8_t
	{
		Empty,
		Roll,
		LifedRoll
	};

	int16_t width{ 0 };

	int16_t height{ 0 };

	std::vector<FloorTile> floorTiles{};

	void parseInput();

	FloorTile getTileAt(int16_t x, int16_t y);

	void setTileAt(int16_t x, int16_t y, FloorTile tile);

	size_t liftPossibleRolls(bool verbose = false);

	int countAround(int16_t x, int16_t y, int lazyLimit = 4);

	static bool registered;
};
