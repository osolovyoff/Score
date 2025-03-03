#pragma once

#include <Game/Units/Unit.hpp>

namespace sw
{
	class Swordsman: public Unit<io::SpawnSwordsman>
	{
	public:
		Swordsman(const io::SpawnSwordsman& data): Unit(data) {}
	};
}
