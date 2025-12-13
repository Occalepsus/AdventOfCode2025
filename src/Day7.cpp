#include "Day7.h"

#include "DayFactory.h"

bool Day7::registered = []() {
	DayFactory::get().registerDay(7, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day7>();
		});
	return true;
}();

Day7::Day7()
	: DayInterface(7, true)
{
	parseInput();
}

size_t Day7::part1()
{
	int startCol{ static_cast<int>(inputLines[0].find('S')) };

	return emitRaySimple(startCol, 0);
}

size_t Day7::part2()
{
	int startCol{ static_cast<int>(inputLines[0].find('S')) };

	// Idk why but emitRayMulti counts one less than expected
	return emitRayMulti(startCol, 0) + 1;
}

void Day7::parseInput()
{
	splitterCols.clear();

	splitterCols.resize(inputLines[0].size());

	int height{ 0 };
	for (const std::string& line : inputLines)
	{
		int col{ 0 };
		for (char ch : line)
		{
			if (ch == '^')
			{
				splitterCols[col].emplace_back(Splitter{.height = height});
			}
			++col;
		}

		++height;
	}
}

size_t Day7::emitRaySimple(int col, int height)
{
	for (std::vector<Splitter>& splitterCol{ splitterCols[col] }; 
		Splitter& splitter : splitterCol)
	{
		if (height <= splitter.height)
		{
			if (!splitter.hasSplit)
			{
				splitter.hasSplit = true;
				return 1 + emitRaySimple(col - 1, splitter.height) + emitRaySimple(col + 1, splitter.height);
			}

			break;
		}
	}

	// Ray goes through, do not split
	return 0;
}

size_t Day7::emitRayMulti(int col, int height)
{
	for (std::vector<Splitter>& splitterCol{ splitterCols[col] }; 
		Splitter& splitter : splitterCol)
	{
		if (height <= splitter.height)
		{
			// If split after is not known, compute it
			if (splitter.splitAfter == 0)
			{
				splitter.splitAfter = 1 + emitRayMulti(col - 1, splitter.height) + emitRayMulti(col + 1, splitter.height);
			}

			return splitter.splitAfter;
		}
	}

	// Ray goes through, do not split
	return 0;
}