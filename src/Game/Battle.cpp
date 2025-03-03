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
	_tickId++;
	return _map->update(_tickId); // update will return false if there are no units moving
}

void sw::Battle::process(const io::CreateMap& data)
{
	if (!_map)
	{
		_map.reset(new Map(data.width, data.height)); 
		if (_map)
			_eventLog.log(_tickId, io::MapCreated{data.width, data.height});
	}
}

void sw::Battle::process(const io::SpawnHunter& data)
{
	std::shared_ptr<IUnit> unit = std::make_shared<Hunter>(data);
	_map->placeUnit(data.x, data.y, std::dynamic_pointer_cast<IUnit>(unit));
	_eventLog.log(_tickId, io::UnitSpawned{data.unitId, "Hunter", data.x, data.y});
}

void sw::Battle::process(const io::SpawnSwordsman& data)
{
	_map->placeUnit(data.x, data.y, std::make_shared<Swordsman>(data));
	_eventLog.log(_tickId, io::UnitSpawned{data.unitId, "Swordsman", data.x, data.y});
}

void sw::Battle::process(const io::March& data)
{
	std::shared_ptr<IUnit> unit = _map->getUnit(data.unitId);
	if (unit)
	{
		const auto pos = unit->getPosition();
		unit->setTarget(data.targetX, data.targetY);
		_eventLog.log(_tickId, io::MarchStarted{data.unitId, pos.x, pos.y, data.targetX, data.targetY});
	}
	else
	{
		// TODO: log error
	}
}