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
		static GameSession& getInstance();

		template <typename TCommandData>
		void process(const TCommandData& data)
		{
			battle.process(1, data);
		}

		void run()
		{
			while (true)
			{
				battle.play();
			}
		}
	};
}
