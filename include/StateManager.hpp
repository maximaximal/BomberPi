#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#include <vector>
#include <State.hpp>
#include <SDLEventHandler.hpp>

namespace Client
{
    class Window;
    class TextureManager;
}

class StateManager : public SDLEventHandler
{
    public:
        void push(std::shared_ptr<State> state);
        void pop();
        std::shared_ptr<State> top();

        void render(std::shared_ptr<Client::Window> window);
        void setTextureManager(std::shared_ptr<Client::TextureManager> textureManager);
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
    private:
        std::vector<std::shared_ptr<State>> m_states;
        std::shared_ptr<Client::TextureManager> m_textureManager;
};

#endif
