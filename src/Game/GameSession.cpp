#include "GameSession.hpp"
// Singleton, not thread-safe. Sorry, I can place it in main.cpp, but it's not so important for this task.
sw::GameSession& sw::GameSession::getInstance()
{
	static GameSession instance;
	return instance;
}
