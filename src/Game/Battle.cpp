#include "Battle.hpp"

#include "Map.hpp"

#include "IO/Commands/CreateMap.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "Units/Hunter.hpp"
#include "Units/Swordsman.hpp"
#include "Units/Unit.hpp"

bool sw::Battle::play()
{
	const bool isFinal = map->update(tickId);
	tickId++;
	return isFinal;
}

void sw::Battle::process(int tick_id, const io::CreateMap& data)
{
	if (!map)
	{
		map.reset(new Map(data.width, data.height)); 
		if (map)
			eventLog.log(tick_id, io::MapCreated{data.width, data.height});
	}
}

void sw::Battle::process(int tick_id, const io::SpawnHunter& data)
{
	std::shared_ptr<IUnit> unit = std::make_shared<Hunter>(data);
	map->placeUnit(data.x, data.y, std::dynamic_pointer_cast<IUnit>(unit));
	eventLog.log(tick_id, io::UnitSpawned{data.unitId, "Hunter", data.x, data.y});
}

void sw::Battle::process(int tick_id, const io::SpawnSwordsman& data)
{
	map->placeUnit(data.x, data.y, std::make_shared<Swordsman>(data));
	eventLog.log(tick_id, io::UnitSpawned{data.unitId, "Swordsman", data.x, data.y});
}

void sw::Battle::process(int tick_id, const io::March& data)
{
	std::shared_ptr<IUnit> unit = map->getUnit(data.unitId);
	if (!unit) return; 

	const auto pos = unit->getPosition();
	unit->setTarget(data.targetX, data.targetY);
	eventLog.log(tick_id, io::MarchStarted{data.unitId, pos.x, pos.y, data.targetX, data.targetY});
}