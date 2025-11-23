#include "DayFactory.h"

DayFactory& DayFactory::get()
{
	static DayFactory instance{};
	return instance;
}

void DayFactory::registerDay(int day, const std::function<std::unique_ptr<DayInterface>()>& creator)
{
	creators[day] = creator;
}

std::unique_ptr<DayInterface> DayFactory::createDay(int day)
{
	if (auto it = creators.find(day);
		it != creators.end())
	{
		// Call the creator function to create an instance of the day
		return it->second();
	}
	return nullptr;
}