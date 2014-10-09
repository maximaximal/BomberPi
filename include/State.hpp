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
        StateManager* getStateManager();

        void setHandlers(StateManager *stateManager);
        void setTextureManager(Client::TextureManager *textureManager);
        void setFontManager(PiH::FontManager *fontManager);

        virtual void render(Client::Window *window);
        virtual void update(float frameTime);
    	private:
		std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
        Client::TextureManager *m_textureManager;
        StateManager* m_stateManager;
        PiH::FontManager *m_fontManager;
};

#endif
