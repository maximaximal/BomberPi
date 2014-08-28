#include <State.hpp>
#include <SDLEventHandler.hpp>

std::shared_ptr<SDLEventHandler> State::getSDLEventHandler()
{
    if(!m_sdlEventHandler)
        m_sdlEventHandler = std::make_shared<SDLEventHandler>();
    return m_sdlEventHandler;
}

StateManager* State::getStateManager()
{
    return m_stateManager;
}

void State::setHandlers(StateManager *stateManager)
{
    m_stateManager = stateManager;
}

void State::render(std::shared_ptr<Client::Window> window)
{

}
