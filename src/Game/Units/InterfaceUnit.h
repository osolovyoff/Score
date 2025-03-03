#pragma once
#include <cstdint>

namespace sw
{
	struct Vector2
	{
		uint32_t x;
		uint32_t y;
	};

	class Map;

	class IUnit
	{
	public:
		virtual ~IUnit() = default;
		virtual uint32_t getId() const = 0;
		virtual bool isAlive() const = 0;
		virtual void update(uint32_t tickId, Map* map) = 0;
		virtual void takeDamage(uint32_t tickId, uint32_t damage, uint32_t attackerUnitId) = 0;
		virtual void setTarget(uint32_t x, uint32_t y) = 0;
		virtual void setPosition(uint32_t x, uint32_t y) = 0;
		virtual Vector2 getPosition() const = 0;
	};
}
