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
