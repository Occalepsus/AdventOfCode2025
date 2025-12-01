#include "Day1.h"

#include "DayFactory.h"
#include "Utilities.h"

#include <iostream>

bool Day1::registered = []() {
	DayFactory::get().registerDay(1, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day1>();
		});
	return true;
}();

Day1::Day1()
	: DayInterface(1, true)
{}

size_t Day1::part1()
{
	size_t res{ 0 };

	int dialPosition{ 50 };

	// For each line, get the move count and direction
	for (auto& line : inputLines)
	{
		int move{ std::stoi(line.data() + 1) };

		if (line[0] == 'L')
		{
			dialPosition -= move;
		}
		else if (line[0] == 'R')
		{
			dialPosition += move;
		}

		// If the dial position is at a multiple of 100, increment res
		if (dialPosition % 100 == 0)
		{
			res++;
		}
	}

	return res;
}

size_t Day1::part2()
{
	size_t res{ 0 };

	int dialPosition{ 50 };

	// Same as part 1
	for (auto& line : inputLines)
	{
		int move{ std::stoi(line.data() + 1) };

		// "Normalize" moves over 100
		res += move / 100;
		move %= 100;

		if (line[0] == 'L')
		{
			// If dial was at 0, and we move left, do not count as crossing
			if (dialPosition == 0)
			{
				res--;
			}

			dialPosition -= move;
		}
		else if (line[0] == 'R')
		{
			dialPosition += move;
		}

		// If the dial position is at or beyond 100 or at or below 0, it means we crossed a multiple of 100
		// Since we normalized above, this happens only once per move maximum
		if (dialPosition >= 100 || dialPosition <= 0)
		{
			res++;
		}

		// Normalize dial position to be within 0-99
		dialPosition = Utilities::positiveModulo(dialPosition, 100);
	}

	return res;
}