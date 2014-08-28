#ifndef CLIENT_GAME_HPP_INCLUDED
#define CLIENT_GAME_HPP_INCLUDED

#include <memory>
#include <Client/Window.hpp>
#include <StateManager.hpp>
#include <Client/TextureManager.hpp>

namespace Client 
{
    class Game
    {
		public:
			Game();
			virtual ~Game();

			int init();

			void update(float frametime);

            void onEvent(const SDL_Event &e);

			void render();
		private:
			std::shared_ptr<Window> m_window;
            std::shared_ptr<StateManager> m_stateManager;
            std::shared_ptr<TextureManager> m_textureManager;
    };
}


#endif
