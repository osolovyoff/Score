#pragma once
#include "Game/Map.hpp"
#include "Game/Battle.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"

#include "InterfaceUnit.hpp"
#include "IO/Events/MarchEnded.hpp"

namespace sw
{
	template <typename T>
	class Unit: public IUnit
	{
	protected:
		static constexpr uint32_t minimum_range = 2;
		T _data;
		bool _isMoving = false;
		Vector2 _target, _position;

	public:
		Unit(const T& data): _data(data){} 
		uint32_t getId() const override { return _data.unitId; }
		bool isAlive() const override { return _data.hp > 0; }

		bool update(uint32_t tickId, Map* map) override
		{
			if (_data.hp == 0)
			{
				return false;
			}

			const bool wasAction = this->action(tickId, map);
			if (wasAction) return true;

			if (_isMoving)
			{
				_isMoving = moveTo(_target.x, _target.y);
				if (_isMoving)
					EventLog().log(tickId, io::UnitMoved{getId(), _position.x, _position.y});
				else
					EventLog().log(tickId, io::MarchEnded{getId(), _position.x, _position.y});
				return true;
			}
			return false;
		}

		void setTarget(uint32_t x, uint32_t y) override
		{
			_target.x = x;
			_target.y = y;
			_isMoving = true;
		}

		void setPosition(uint32_t x, uint32_t y) override
		{
			_position.x = x;
			_position.y = y;
		}

		Vector2 getPosition() const override
		{
			return _position;
		}

	protected:
		virtual bool moveTo(uint32_t x, uint32_t y)
		{
			const int direction_x = _target.x - _position.x;
			const int direction_y = _target.y - _position.y;
			if (direction_x != 0)
				_position.x += direction_x > 0 ? 1 : -1;
			else if (direction_y != 0)
				_position.y += direction_y > 0 ? 1 : -1;
			else
				return false;
			return true;
		}

		bool action(uint32_t tickId, Map* map) override
		{
			const uint32_t attackerUnitId = getId();
			auto Victim = map->getClosestUnit(attackerUnitId);
			if (Victim)
			{
				const Vector2 posVictim = Victim->getPosition();
				const float distance = std::sqrt(std::pow(posVictim.x - _position.x, 2) + std::pow(posVictim.y - _position.y, 2));
				if (distance < minimum_range)
				{
					Victim->takeDamage(tickId, _data.strength, attackerUnitId);
					return true;
				}
			}
			return false;
		}

		void takeDamage(uint32_t tick_id, uint32_t damage, uint32_t attackerUnitId) override
		{
			const int health = _data.hp - damage;
			const uint32_t victimUnitId = getId();

			EventLog log;
			if (health <= 0)
			{
				_data.hp = 0;
				log.log(tick_id, io::UnitDied{victimUnitId});
			}
			else
			{
				_data.hp -= damage;
				log.log(tick_id, io::UnitAttacked{attackerUnitId, victimUnitId, damage, _data.hp});
			}
		}
	};
}


