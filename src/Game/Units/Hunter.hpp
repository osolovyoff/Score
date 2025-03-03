#pragma once

#include <cstdint>
#include <IO/Commands/SpawnHunter.hpp>

#include "Unit.hpp"


namespace sw
{
	class Hunter: public Unit<io::SpawnHunter>
	{
	public:
		Hunter(const io::SpawnHunter& data) : Unit(data) {}

		bool action(uint32_t tickId, Map* map) override
		{
			const bool wasCloseCombatAction = Unit<io::SpawnHunter>::action(tickId, map);
			if (wasCloseCombatAction) return true;

			const uint32_t attackerUnitId = getId();
			auto unit = map->getUnitInRange(attackerUnitId, minimum_range, _data.range);
			if (unit)
			{
				unit->takeDamage(tickId,_data.agility, attackerUnitId);
				return true;
			}
			return false;
		}

	};
}
