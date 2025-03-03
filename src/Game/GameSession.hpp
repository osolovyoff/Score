#pragma once
#include <any>
#include <variant>
#include "Units/Unit.hpp"

namespace sw
{
	class GameSession
	{
		using Options = std::variant<io::CreateMap, io::March, io::SpawnHunter, io::SpawnSwordsman>;
	private:
		Battle battle;
		std::list<Options> _cmds;
		// std::list<std::shared_ptr<IUnit>> _commands;

	public:
		GameSession() = default;

		static GameSession& getInstance();

		template <typename TCommandData>
		void process(const TCommandData& data)
		{
			battle.act(1, data);
			// _cmds.push_back(std::any_cast<TCommandData>(data));
			// auto unit = std::make_shared<Unit<TCommandData>>(data);
			// _commands.push_back(unit);
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
