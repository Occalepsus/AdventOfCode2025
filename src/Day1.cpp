#include "Day1.h"

#include "DayFactory.h"

bool Day1::registered = []() {
	DayFactory::get().registerDay(1, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day1>();
		});
	return true;
}();

Day1::Day1()
	: DayInterface(1)
{}

size_t Day1::part1()
{
	size_t res{ 0 };

	return res;
}

size_t Day1::part2()
{
	size_t res{ 0 };

	return res;
}