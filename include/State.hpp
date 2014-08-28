#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include <memory>

class SDLEventHandler;
class GameEventHandler;
class StateManager;

namespace Client
{
	class Window;
}

class State
{
    public:
		std::shared_ptr<SDLEventHandler> getSDLEventHandler();
        std::shared_ptr<GameEventHandler> getGameEventHandler();
        StateManager* getStateManager();

        void setHandlers(StateManager *stateManager);

        void render(std::shared_ptr<Client::Window> window);
    private:
		std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
        std::shared_ptr<GameEventHandler> m_gameEventHandler;
        StateManager* m_stateManager;
};

#endif
