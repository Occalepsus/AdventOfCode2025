#pragma once

#include "DayInterface.h"

#include <unordered_map>
#include <functional>
#include <memory>

class DayFactory
{
public:
	static DayFactory& get();

	void registerDay(int day, const std::function<std::unique_ptr<DayInterface>()>& creator);

	std::unique_ptr<DayInterface> createDay(int day);

private:
	std::unordered_map<int, std::function<std::unique_ptr<DayInterface>()>> creators;

	DayFactory() = default;
	~DayFactory() = default;
	DayFactory(const DayFactory&) = delete;
	DayFactory& operator=(const DayFactory&) = delete;
};