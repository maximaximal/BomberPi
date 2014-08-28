#include <GameEventHandler.hpp>

void GameEventHandler::sendEvent(GameEventHandler::Type eventType, float frametime)
{
    onGameEvent(eventType, frametime);
	m_signals[eventType](eventType, frametime);
}

GameEventHandler::GameEventSignal GameEventHandler::getSignal(const GameEventHandler::Type &type)
{
    return m_signals[type];
}

void GameEventHandler::onGameEvent(GameEventHandler::Type eventType, float frameTime)
{
    //Nothing to do here - this function can be derived from.
}
