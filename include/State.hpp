#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include <memory>

class SDLEventHandler;
class StateManager;

namespace Client
{
	class Window;
	class TextureManager;
}

namespace PiH
{
    class FontManager;
}

class State
{
    public:
		std::shared_ptr<SDLEventHandler> getSDLEventHandler();
		Client::TextureManager *getTextureManager();
        PiH::FontManager *getFontManager();
        StateManager* getStateManager();
        Client::Window* getWindow();

        void setHandlers(StateManager *stateManager);
        void setTextureManager(Client::TextureManager *textureManager);
        void setFontManager(PiH::FontManager *fontManager);
        void setWindow(Client::Window *window);

        virtual void render(Client::Window *window);
        virtual void update(float frameTime);
	private:
		std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
        Client::TextureManager *m_textureManager;
        StateManager *m_stateManager;
        PiH::FontManager *m_fontManager;
        Client::Window *m_window;
};

#endif
