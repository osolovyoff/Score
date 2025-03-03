#include "Map.hpp"

#include <math.h>

#include "IO/System/EventLog.hpp"
#include "Units/Unit.hpp"

namespace sw
{
	bool Map::isValidPosition(uint32_t x, uint32_t y) const
	{
		return 0 <= x && x < width && 0 <= y && y < height;
	}

	void Map::kill(uint32_t unitId)
	{
		auto unit = getUnit(unitId);
		units.erase(unitId);
	}

	std::shared_ptr<IUnit> Map::getClosestUnit(uint32_t excludeUnitId) const
	{
		auto attacker = getUnit(excludeUnitId);
		if (!attacker)
			return nullptr;

		const auto pos = attacker->getPosition();
		uint32_t closestUnitId = excludeUnitId;
		float closestDistance = std::numeric_limits<float>::max();
		for (auto& unit : units)
		{
			if (unit.first == excludeUnitId)
				continue;

			auto unitPos = unit.second->getPosition();
			const float length = std::sqrt(std::pow(unitPos.x - pos.x, 2) + std::pow(unitPos.y - pos.y, 2));
			if (length < closestDistance)
			{
				closestDistance = length;
				closestUnitId = unit.first;
			}
		}
		if (closestUnitId == excludeUnitId)
			return nullptr;
		return getUnit(closestUnitId);
	}

	std::shared_ptr<IUnit> Map::getUnitInRange(uint32_t excludeUnitId, uint32_t rangeMin, uint32_t rangeMax) const
	{
		for (auto& unit : units)
		{
			if (unit.first == excludeUnitId)
				continue;

			auto unitPos = unit.second->getPosition();
			auto attacker = getUnit(excludeUnitId);
			if (!attacker)
				return nullptr;

			const auto pos = attacker->getPosition();
			const float length = std::sqrt(std::pow(unitPos.x - pos.x, 2) + std::pow(unitPos.y - pos.y, 2));
			if (rangeMin <= length && length <= rangeMax)
				return unit.second;
		}
		return nullptr;
	}

	std::shared_ptr<sw::IUnit> Map::getUnit(uint32_t id) const
	{
		auto e = units.find(id);
		if (e == units.end())
			return nullptr;
		return e->second;
	}

	bool Map::update(uint32_t tickId)  
	{
		const bool isEnd = false;
		for (auto& unit : units)
		{
			if (unit.second->isAlive())
				unit.second->update(tickId, this);
		}
		std::erase_if(units, [](auto& pair) { return !pair.second->isAlive(); });
		return isEnd;
	}

	void Map::placeUnit(uint32_t x, uint32_t y, std::shared_ptr<IUnit> unit)
	{
		const int id = unit->getId();
		units[id] = unit;
		unit->setPosition(x, y);
	}
}
