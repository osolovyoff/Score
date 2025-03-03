#pragma once

#include "IO/Events/UnitSpawned.hpp"
#include "IO/System/EventLog.hpp"

#include <cstdint>

#include <Game/Units/Unit.hpp>
#include <IO/Commands/SpawnHunter.hpp>

namespace sw
{
	class Swordsman: public Unit<io::SpawnSwordsman>
	{
	public:
		Swordsman(const io::SpawnSwordsman& data): Unit(data) {}
	};
}
