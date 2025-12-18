#pragma once

#include "DayInterface.h"

#include <unordered_set>

class Day8 : public DayInterface
{
public:
	Day8();

	~Day8() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	struct Box;

	using Network = std::unordered_set<Box*>;

	struct Box
	{
		int x{ 0 };
		int y{ 0 };
		int z{ 0 };

		// If nullptr, box is its own network
		Network* connectedNetwork{ nullptr };

		explicit Box(const std::string& fromStr);
	};

	struct Link
	{
		Box* boxA{ nullptr };
		Box* boxB{ nullptr };

		double distance{ -1 };
	};

	std::vector<std::unique_ptr<Box>> boxes;
	std::list<Network> networks;

	void parseBoxes();

	// If linkCounts is -1, make all links
	std::vector<Link> makeLinks(int linkCounts = -1) const;

	bool connectBoxes(Box& boxA, Box& boxB);

	static bool registered;
};
