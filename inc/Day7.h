#pragma once

#include "DayInterface.h"

class Day7 : public DayInterface
{
public:
	Day7();

	~Day7() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	struct Splitter
	{
		int height{ 0 };

		bool hasSplit{ false };

		// The number of paths possible for a ray that touches this splitter (counting itself)
		// If 0, it has not been calculated yet
		size_t splitAfter{ 0 };
	};

	std::vector<std::vector<Splitter>> splitterCols{};

	void parseInput();

	size_t emitRaySimple(int col, int height);

	size_t emitRayMulti(int col, int height);

	static bool registered;
};
