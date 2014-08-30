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

class State
{
    public:
		std::shared_ptr<SDLEventHandler> getSDLEventHandler();
		std::shared_ptr<Client::TextureManager> getTextureManager();
        StateManager* getStateManager();

        void setHandlers(StateManager *stateManager);
        void setTextureManager(std::shared_ptr<Client::TextureManager> textureManager);

        virtual void render(std::shared_ptr<Client::Window> window);
        virtual void update(float frameTime);
    	private:
		std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
        std::shared_ptr<Client::TextureManager> m_textureManager;
        StateManager* m_stateManager;
};

#endif
