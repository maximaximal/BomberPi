#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#include <vector>
#include <State.hpp>
#include <SDLEventHandler.hpp>
#include <GameEventHandler.hpp>

namespace Client
{
    class Window;
}

class StateManager : public SDLEventHandler, public GameEventHandler
{
    public:
        void push(std::shared_ptr<State> state);
        void pop();
        std::shared_ptr<State> top();

        void render(std::shared_ptr<Client::Window> window);
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
        virtual void onGameEvent(Type e, float frametime);
    private:
        std::vector<std::shared_ptr<State>> m_states;
};

#endif
