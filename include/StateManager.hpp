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
namespace PiH
{
    class FontManager;
}

class StateManager : public SDLEventHandler
{
    public:
        void push(std::shared_ptr<State> state);
        void pop();
        std::shared_ptr<State> top();

        void render(Client::Window *window);
        void update(float frameTime);
        void setTextureManager(Client::TextureManager *textureManager);
        void setFontManager(PiH::FontManager *fontManager);
        void setWindow(Client::Window *window);

        Client::Window* getWindow();
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
    private:
        std::vector<std::shared_ptr<State>> m_states;
        Client::TextureManager *m_textureManager;
        Client::Window *m_window;
        PiH::FontManager *m_fontManager;
};

#endif
