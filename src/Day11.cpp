#include "Day11.h"

#include "DayFactory.h"

bool Day11::registered = []() {
	DayFactory::get().registerDay(11, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day11>();
		});
	return true;
}();

Day11::Day11()
	: DayInterface(11, true)
{
	parseNodes();
}

size_t Day11::part1()
{
	// Part 2 compatibility: ("you" or "svr" node)
	Node* startNode;
	if (nodes.contains("you"))
	{
		startNode = &nodes.at("you");
	}
	else
	{
		startNode = &nodes.at("svr");
	}

	return computePathsFrom(*startNode);
}

size_t Day11::part2()
{
	// Count paths "svr" -> "fft" -> "dac" -> "out"
	resetPathCounts(&nodes.at("fft"));
	int pathsvrToFft{ computePathsFrom(nodes.at("svr")) };

	resetPathCounts(&nodes.at("dac"));
	int pathFftToDac{ computePathsFrom(nodes.at("fft")) };

	resetPathCounts(&nodes.at("out"));
	int pathDacToOut{ computePathsFrom(nodes.at("dac")) };

	// Alternatively, count paths "svr" -> "dac" -> "fft" -> "out"
	resetPathCounts(&nodes.at("dac"));
	int pathsvrToDac{ computePathsFrom(nodes.at("svr")) };

	resetPathCounts(&nodes.at("fft"));
	int pathDacToFft{ computePathsFrom(nodes.at("dac")) };

	resetPathCounts(&nodes.at("out"));
	int pathFftToOut{ computePathsFrom(nodes.at("fft")) };

	return static_cast<size_t>(pathsvrToFft) * pathFftToDac * pathDacToOut + static_cast<size_t>(pathsvrToDac) * pathDacToFft * pathFftToOut;
}

void Day11::parseNodes()
{
	nodes = { {"out", Node()} };

	// First pass: create all nodes
	for (const std::string& line : inputLines)
	{
		nodes.try_emplace(line.substr(0, 3));
	}

	// nodes container will not be modified beyond this point, so we can use pointers on nodes safely.

	// Second pass: link nodes
	for (const std::string& line : inputLines)
	{
		Node& fromNode{ nodes.at(line.substr(0, 3)) };
		size_t pos{ 5 };
		while (pos < line.size())
		{
			std::string toNodeName{ line.substr(pos, 3) };
			Node& toNode{ nodes.at(toNodeName) };
			fromNode.to.push_back(&toNode);
			toNode.from.push_back(&fromNode);
			pos += 4;
		}
	}

	nodes.at("out").pathCountToOut = 1;
}

void Day11::resetPathCounts(Node* toNode)
{
	for (auto& [_, node] : nodes)
	{
		node.pathCountToOut = -1;
	}

	toNode->pathCountToOut = 1;
}

int Day11::computePathsFrom(Node& fromNode)
{
	if (fromNode.pathCountToOut == -1)
	{
		fromNode.pathCountToOut = 0;

		for (Node* toNode : fromNode.to)
		{
			fromNode.pathCountToOut += computePathsFrom(*toNode);
		}
	}

	return fromNode.pathCountToOut;
}