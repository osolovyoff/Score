#pragma once

#include <memory>
#include <unordered_map>

namespace sw
{
	class IUnit;
	using SharedUnit = std::shared_ptr<IUnit>;

	class Map
	{
	protected:
		uint32_t _width, _height; 
		std::unordered_map<uint32_t, SharedUnit> _units;

	public:
		Map(uint32_t width, uint32_t height) : _width(width), _height(height) {}
		bool update(uint32_t tickId);

		void placeUnit(uint32_t x, uint32_t y, std::shared_ptr<IUnit> unit);

		std::shared_ptr<IUnit> getUnit(uint32_t unitId) const;
		std::shared_ptr<IUnit> getClosestUnit(uint32_t excludeUnitId) const;
		std::shared_ptr<IUnit> getUnitInRange(uint32_t excludeUnitId, uint32_t rangeMin, uint32_t rangeMax) const;
	};
}


