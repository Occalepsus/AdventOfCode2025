#include <iostream>

#include "Utilities.h"
#include "DayFactory.h"

int main()
{
	const int dayNumber{ 2 };

    std::unique_ptr<DayInterface> day{ DayFactory::get().createDay(dayNumber) };

    size_t res1{ day->part1() };

    std::cout << "Day" << dayNumber << ", part 1 result: " << res1 << "\n";

	size_t res2{ day->part2() };

    std::cout << "Day" << dayNumber << ", part 2 result: " << res2 << "\n";
	return 0;
}