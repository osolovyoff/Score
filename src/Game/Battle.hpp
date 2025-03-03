﻿#pragma once

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
		EventLog			 eventLog;
		int32_t 			 tickId = 2;
		std::unique_ptr<Map> map;

		bool play();

		void process(int tick_id, const io::CreateMap& data);
		void process(int tick_id, const io::SpawnHunter& data);
		void process(int tick_id, const io::SpawnSwordsman& data);
		void process(int tick_id, const io::March& data);

		template <typename TCommandData>
		void process(int tick_id, const TCommandData& data)
		{
			static_assert(false, "Unknown command");
		}
	};
}
