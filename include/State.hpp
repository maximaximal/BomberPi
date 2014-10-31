#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include <memory>

class SDLEventHandler;
class StateManager;

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
namespace piga
{
    class GameEventHandler;
    class Interface;
}

class State
{
    public:
        std::shared_ptr<SDLEventHandler> getSDLEventHandler();
        std::shared_ptr<piga::GameEventHandler> getGameEventHandler();
		Client::TextureManager *getTextureManager();
        PiH::FontManager *getFontManager();
        StateManager* getStateManager();
        Client::Window* getWindow();
        Client::Config *getConfig();
        piga::Interface *getInterface();

        void setHandlers(StateManager *stateManager);
        void setTextureManager(Client::TextureManager *textureManager);
        void setFontManager(PiH::FontManager *fontManager);
        void setWindow(Client::Window *window);
        void setConfig(Client::Config *config);
        void setInterface(piga::Interface *interface);

        virtual void render(Client::Window *window);
        virtual void update(float frameTime);
	private:
        std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
        std::shared_ptr<piga::GameEventHandler> m_gameEventHandler;
        Client::TextureManager *m_textureManager;
        StateManager *m_stateManager;
        PiH::FontManager *m_fontManager;
        Client::Window *m_window;
        Client::Config *m_config;
        piga::Interface *m_pigaInterface;
};

#endif
