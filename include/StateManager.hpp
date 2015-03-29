#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#include <vector>
#include <State.hpp>
#include <SDLEventHandler.hpp>
#include <piga/GameEventHandler.hpp>
#include <piga/Interface.hpp>

namespace Client
{
    class Window;
    class TextureManager;
    class Config;
}
namespace PiH
{
    class FontManager;
}

class StateManager : public SDLEventHandler, public piga::GameEventHandler
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
        void setConfig(Client::Config *config);
        void setPigaInterface(piga::Interface *interface);
        void quit();

        Client::Window* getWindow();
        bool hasBeenQuitted();
    protected:
        virtual void onSDLEvent(const SDL_Event &e, float frametime);
        virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);
    private:
        std::vector<std::shared_ptr<State>> m_states;
        Client::TextureManager *m_textureManager;
        Client::Window *m_window;
        Client::Config *m_config;
        PiH::FontManager *m_fontManager;
        piga::Interface *m_pigaInterface;
        bool m_quit = false;
};

#endif
