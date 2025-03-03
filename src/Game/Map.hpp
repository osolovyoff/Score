#pragma once

#include "IO/Commands/SpawnSwordsman.hpp"

#include <memory>
#include <unordered_map>


namespace sw
{
	class IUnit;
	using SharedUnit = std::shared_ptr<IUnit>;

	class Map
	{
	protected:
		uint32_t width, height; // TODO: change to _
		std::unordered_map<uint32_t, SharedUnit> units; // _

	public:
		Map(size_t width, size_t height) : width(width), height(height) {}
		bool update(uint32_t tickId);

		void placeUnit(uint32_t x, uint32_t y, std::shared_ptr<IUnit> unit);
		bool isValidPosition(uint32_t x, uint32_t y) const;
		void kill(uint32_t unitId);

		std::shared_ptr<IUnit> getUnit(uint32_t unitId) const;
		std::shared_ptr<IUnit> getClosestUnit(uint32_t excludeUnitId) const;
		std::shared_ptr<IUnit> getUnitInRange(uint32_t excludeUnitId, uint32_t rangeMin, uint32_t rangeMax) const;
	};
}


