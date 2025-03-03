#include "Map.hpp"

#include <cmath>

#include <IO/System/EventLog.hpp>
#include <Game/Units/Unit.hpp>

namespace sw
{
	std::shared_ptr<IUnit> Map::getClosestUnit(uint32_t excludeUnitId) const
	{
		auto attacker = getUnit(excludeUnitId);
		if (!attacker)
			return nullptr;

		const auto posAttacker = attacker->getPosition();
		uint32_t closestUnitId = excludeUnitId;
		double closestDistance = std::numeric_limits<double>::max();
		for (auto& victim : _units)
		{
			if (victim.first == excludeUnitId || !victim.second->isAlive())
				continue;

			const auto posVictim = victim.second->getPosition();
			const int difX(posVictim.x - posAttacker.x), difY(posVictim.y - posAttacker.y);
			const double length = std::sqrt(std::pow(difX, 2) + std::pow(difY, 2));
			if (length < closestDistance)
			{
				closestDistance = length;
				closestUnitId = victim.first;
			}
		}
		if (closestUnitId == excludeUnitId)
			return nullptr;
		return getUnit(closestUnitId);
	}

	std::shared_ptr<IUnit> Map::getUnitInRange(uint32_t excludeUnitId, uint32_t rangeMin, uint32_t rangeMax) const
	{
		auto attacker = getUnit(excludeUnitId);
		if (!attacker)
			return nullptr;

		std::shared_ptr<IUnit> result;
		
		const auto posAttacker = attacker->getPosition();
		for (auto& unit : _units)
		{
			if (unit.first == excludeUnitId || !unit.second->isAlive())
				continue;

			const auto victim = unit.second;
			const auto posVictim = victim->getPosition();

			const int difX(posVictim.x - posAttacker.x), difY(posVictim.y - posAttacker.y);
			const double length = std::sqrt(std::pow(difX, 2) + std::pow(difY, 2));
			if (rangeMin <= length && length <= rangeMax)
			{
				result = victim;
			}
		}
		return result;
	}

	std::shared_ptr<sw::IUnit> Map::getUnit(uint32_t id) const
	{
		auto e = _units.find(id);
		if (e == _units.end())
			return nullptr;
		return e->second;
	}

	bool Map::update(uint32_t tickId)  
	{
		bool hasUpdate = false;
		for (auto& unit : _units)
		{
			if (unit.second->isAlive())
				hasUpdate = unit.second->update(tickId, this) || hasUpdate;
		}
		std::erase_if(_units, [](auto& pair) { return !pair.second->isAlive(); });
		return !hasUpdate;
	}

	void Map::placeUnit(uint32_t x, uint32_t y, std::shared_ptr<IUnit> unit)
	{
		const uint32_t id = unit->getId();
		_units[id] = unit;
		unit->setPosition(x, y);
	}
}
