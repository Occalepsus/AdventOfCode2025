#include "Day8.h"

#include "DayFactory.h"

#include <algorithm>

bool Day8::registered = []() {
	DayFactory::get().registerDay(8, []() -> std::unique_ptr<DayInterface> {
		return std::make_unique<Day8>();
		});
	return true;
}();

Day8::Day8()
	: DayInterface(8, true)
{
}

size_t Day8::part1()
{
	parseBoxes();
	networks.clear();

	auto links{ makeLinks() };

	std::ranges::sort(links, [](const Link& a, const Link& b) {
		return a.distance < b.distance;
		}
	);

	int linksUsed{ 0 };
	for (const auto& link : links)
	{
		connectBoxes(*link.boxA, *link.boxB);

		if (++linksUsed >= 1000)
		{
			break;
		}
	}

	networks.sort([] (const Network& a, const Network& b) {
		return a.size() > b.size();
		}
	);

	size_t res{ 1 };

	for (int i{ 0 }; i < 3; ++i)
	{
		res *= networks.front().size();
		networks.pop_front();
	}

	return res;
}

size_t Day8::part2()
{
	parseBoxes();
	networks.clear();

	auto links{ makeLinks() };

	std::unordered_set<Box*> connectedBoxes{};
	connectedBoxes.reserve(boxes.size());

	std::ranges::sort(links, [](const Link& a, const Link& b) {
		return a.distance < b.distance;
		}
	);

	for (const auto& link : links)
	{
		connectedBoxes.emplace(link.boxA);
		connectedBoxes.emplace(link.boxB);

		// If all boxes are connected in a sigle network
		if (connectBoxes(*link.boxA, *link.boxB) && networks.size() == 1 && connectedBoxes.size() == boxes.size())
		{
			return static_cast<size_t>(link.boxA->x) * link.boxB->x;
		}
	}

	return 0;
}

void Day8::parseBoxes()
{
	boxes.clear();
	boxes.reserve(inputLines.size());

	for (const std::string& line : inputLines)
	{
		boxes.emplace_back(std::make_unique<Box>(line));
	}
}

std::vector<Day8::Link> Day8::makeLinks(int linkCounts) const
{
	std::vector<Link> links{};

	if (linkCounts > 0)
	{
		links.reserve(linkCounts);
	}

	for (auto boxAIt{ boxes.cbegin() }; boxAIt != boxes.cend(); ++boxAIt)
	{
		for (auto boxBIt{ boxAIt + 1 }; boxBIt != boxes.cend(); ++boxBIt)
		{
			double distance{ std::sqrt(
				std::pow(static_cast<double>(boxAIt->get()->x - boxBIt->get()->x), 2) +
				std::pow(static_cast<double>(boxAIt->get()->y - boxBIt->get()->y), 2) +
				std::pow(static_cast<double>(boxAIt->get()->z - boxBIt->get()->z), 2)
			) };

			links.emplace_back(boxAIt->get(), boxBIt->get(), distance);

			if (linkCounts > 0 && static_cast<int>(links.size()) >= linkCounts)
			{
				return links;
			}
		}
	}

	return links;
}

bool Day8::connectBoxes(Box& boxA, Box& boxB)
{
	if (boxA.connectedNetwork == nullptr && boxB.connectedNetwork == nullptr)
	{
		// Both boxes are not connected to any network yet
		networks.emplace_back();
		Network& newNetwork{ networks.back() };
		newNetwork.insert(&boxA);
		newNetwork.insert(&boxB);
		boxA.connectedNetwork = &newNetwork;
		boxB.connectedNetwork = &newNetwork;
	}
	else if (boxA.connectedNetwork != nullptr && boxB.connectedNetwork == nullptr)
	{
		// Box A is connected, Box B is not
		boxA.connectedNetwork->insert(&boxB);
		boxB.connectedNetwork = boxA.connectedNetwork;
	}
	else if (boxA.connectedNetwork == nullptr && boxB.connectedNetwork != nullptr)
	{
		// Box B is connected, Box A is not
		boxB.connectedNetwork->insert(&boxA);
		boxA.connectedNetwork = boxB.connectedNetwork;
	}
	else if (boxA.connectedNetwork != boxB.connectedNetwork)
	{
		// Both boxes are connected to different networks, merge them
		Network* networkA{ boxA.connectedNetwork };
		Network* networkB{ boxB.connectedNetwork };
		networkA->insert(networkB->begin(), networkB->end());
		for (Box* box : *networkB)
		{
			box->connectedNetwork = networkA;
		}
		networks.remove(*networkB);
	}
	else
	{
		return false;
	}
	return true;
}

Day8::Box::Box(const std::string& fromStr)
{
	size_t pos1 = fromStr.find(',');
	size_t pos2 = fromStr.find(',', pos1 + 1);

	x = std::stoi(fromStr.substr(0, pos1));
	y = std::stoi(fromStr.substr(pos1 + 1, pos2 - pos1 - 1));
	z = std::stoi(fromStr.substr(pos2 + 1));
}
