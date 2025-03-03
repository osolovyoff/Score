#pragma once

#include "Units/Unit.hpp"

namespace sw
{
	class GameSession
	{
	private:
		Battle battle;

	public:
		GameSession() = default;

		template <typename TCommandData>
		void process(const TCommandData& data)
		{
			battle.process(data);
		}

		void run()
		{
			while (true)
				if (battle.play())
					break;
		}
	};
}
