#pragma once

#include "DayInterface.h"

#include <unordered_map>

// Définition d'un hasher transparent pour std::string et std::string_view
struct TransparentStringHash {
	using is_transparent = void;
	size_t operator()(std::string_view txt) const noexcept {
		return std::hash<std::string_view>{}(txt);
	}
	size_t operator()(const std::string& txt) const noexcept {
		return std::hash<std::string>{}(txt);
	}
	size_t operator()(const char* txt) const noexcept {
		return std::hash<std::string_view>{}(txt);
	}
};

class Day11 : public DayInterface
{
public:
	Day11();

	~Day11() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	struct Node
	{
		std::vector<Node*> from{};

		std::vector<Node*> to{};

		int pathCountToOut{ -1 };
	};

	std::unordered_map<std::string, Node, TransparentStringHash, std::equal_to<>> nodes{};

	void parseNodes();

	void resetPathCounts(Node* toNode);

	int computePathsFrom(Node& fromNode);

	static bool registered;
};
