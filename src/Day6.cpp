#include "Day6.h"

#include "DayFactory.h"

#include <algorithm>

namespace
{
	void advanceToNextDigit(const std::string& line, std::string::const_iterator& curValIt)
	{
		curValIt = std::find_if(curValIt, line.cend(), [](char c) { return '0' <= c && c <= '9'; });
	}

	size_t getValAndAdvance(const std::string& line, std::string::const_iterator& curValIt)
	{
		size_t off{ static_cast<size_t>(std::distance(line.cbegin(), curValIt)) };

		auto valEndOff{ line.find(' ', off) };
		size_t valDigitCount{ valEndOff - off };

		size_t val{ std::stoull(line.substr(off, valDigitCount)) };

		curValIt = valEndOff != std::string::npos ? curValIt + valDigitCount : line.cend();
		advanceToNextDigit(line, curValIt);

		return val;
	}
}

bool Day6::registered = []() {
	DayFactory::get().registerDay(6, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day6>();
		});
	return true;
}();

Day6::Day6()
	: DayInterface(6)
{}

size_t Day6::part1()
{
	parseOperands();

	size_t res{ 0 };

	auto valIt0{ inputLines[0].cbegin() };
	auto valIt1{ inputLines[static_cast<size_t>(1) * problemLinesCount].cbegin() };
	auto valIt2{ inputLines[static_cast<size_t>(2) * problemLinesCount].cbegin() };
	auto valIt3{ inputLines[static_cast<size_t>(3) * problemLinesCount].cbegin() };

	advanceToNextDigit(inputLines[0], valIt0);
	advanceToNextDigit(inputLines[static_cast<size_t>(1) * problemLinesCount], valIt1);
	advanceToNextDigit(inputLines[static_cast<size_t>(2) * problemLinesCount], valIt2);
	advanceToNextDigit(inputLines[static_cast<size_t>(3) * problemLinesCount], valIt3);

	char curLine{ 0 };

	for (bool operand : operands)
	{
		if (valIt0 == inputLines[curLine].cend())
		{
			++curLine;
			valIt0 = inputLines[curLine].cbegin();
			valIt1 = inputLines[static_cast<size_t>(1) * problemLinesCount + curLine].cbegin();
			valIt2 = inputLines[static_cast<size_t>(2) * problemLinesCount + curLine].cbegin();
			valIt3 = inputLines[static_cast<size_t>(3) * problemLinesCount + curLine].cbegin();

			advanceToNextDigit(inputLines[curLine], valIt0);
			advanceToNextDigit(inputLines[static_cast<size_t>(1) * problemLinesCount + curLine], valIt1);
			advanceToNextDigit(inputLines[static_cast<size_t>(2) * problemLinesCount + curLine], valIt2);
			advanceToNextDigit(inputLines[static_cast<size_t>(3) * problemLinesCount + curLine], valIt3);
		}

		size_t val0{ getValAndAdvance(inputLines[curLine], valIt0) };
		size_t val1{ getValAndAdvance(inputLines[static_cast<size_t>(1) * problemLinesCount + curLine], valIt1) };
		size_t val2{ getValAndAdvance(inputLines[static_cast<size_t>(2) * problemLinesCount + curLine], valIt2) };
		size_t val3{ getValAndAdvance(inputLines[static_cast<size_t>(3) * problemLinesCount + curLine], valIt3) };

		res += operand ? val0 + val1 + val2 + val3 : val0 * val1 * val2 * val3;
	}

	return res;
}

size_t Day6::part2()
{
	size_t res{ 0 };

	return res;
}

void Day6::parseOperands()
{
	operands.clear();

	for (const auto& line : inputLines)
	{
		if (line.front() == '+' || line.front() == '*')
		{
			++problemLinesCount;

			for (const char c : line)
			{
				if (c == '+' || c == '*')
				{
					operands.push_back(c == '+');
				}
			}
		}
	}
}