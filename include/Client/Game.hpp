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

            void onEvent(const SDL_Event &e, float frametime);

			void render();
		private:
			Window *m_window = nullptr;
            StateManager *m_stateManager = nullptr;
            TextureManager *m_textureManager = nullptr;
    };
}


#endif
