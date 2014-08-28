#include <StateManager.hpp>

void StateManager::push(std::shared_ptr<State> state)
{
    state->setHandlers(this);
    m_states.push_back(state);
}

void StateManager::pop()
{
    m_states.pop_back();
}

std::shared_ptr<State> StateManager::top()
{
    return m_states.back();
}

void StateManager::render(std::shared_ptr<Client::Window> window)
{
    if(m_states.size() > 0)
    {
        top()->render(window);
    }
}

void StateManager::onSDLEvent(const SDL_Event &e, float frametime)
{
    if(m_states.size() > 0)
    {
        top()->getSDLEventHandler()->sendEvent(e, frametime);
    }
}

void StateManager::onGameEvent(GameEventHandler::Type e, float frametime)
{
    if(m_states.size() > 0)
    {
		top()->getGameEventHandler()->sendEvent(e, frametime);
    }
}
