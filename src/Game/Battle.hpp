#pragma once

#include <memory>

#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/Commands/March.hpp"
#include "IO/System/EventLog.hpp"

namespace sw
{
	class Map;
	class Battle
	{
	public:
		EventLog			 _eventLog;
		int32_t 			 _tickId = 1;
		std::unique_ptr<Map> _map;

		bool play();

		void process(const io::CreateMap& data);
		void process(const io::SpawnHunter& data);
		void process(const io::SpawnSwordsman& data);
		void process(const io::March& data);

		template <typename TCommandData>
		void process(const TCommandData& data)
		{
			static_assert(false, "Unknown command");
		}
	};
}
