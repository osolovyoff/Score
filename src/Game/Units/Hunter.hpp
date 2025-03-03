#pragma once

#include <IO/Commands/SpawnHunter.hpp>

#include "Unit.hpp"

#include <cstdint>


namespace sw
{
	class Hunter: public Unit<io::SpawnHunter> // TODO: don't forget to add more diff types of units
	{
	public:
		Hunter(const io::SpawnHunter& data) : Unit(data) {}

		virtual bool action(uint32_t tickId, Map* map) override
		{
			const bool wasAction = Unit<io::SpawnHunter>::action(tickId, map);
			if (wasAction) return true;

			const uint32_t attackerUnitId = getId();
			auto unit = map->getUnitInRange(attackerUnitId, 2, _data.range);
			if (unit)
			{
				unit->takeDamage(tickId,_data.agility, attackerUnitId);
				return true;
			}
			return false;
		}

	};
}
