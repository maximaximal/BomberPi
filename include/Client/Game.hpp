#ifndef CLIENT_GAME_HPP_INCLUDED
#define CLIENT_GAME_HPP_INCLUDED

#include <memory>
#include <Client/Window.hpp>
#include <StateManager.hpp>
#include <Client/TextureManager.hpp>
#include <Client/Config.hpp>
#include <pihud/FontManager.hpp>
#include <piga/Interface.hpp>
#include <InterfaceLogger.hpp>

namespace Client 
{
    class Game
    {
		public:
            Game(bool getCommandsFromSharedMemory = false);
			virtual ~Game();

			int init();

			void update(float frametime);

            void onEvent(const SDL_Event &e, float frametime);

			void render();
		private:
			Window *m_window = nullptr;
            StateManager *m_stateManager = nullptr;
            TextureManager *m_textureManager = nullptr;
            PiH::FontManager *m_fontManager = nullptr;
            Config *m_config = nullptr;
            InterfaceLogger *m_interfaceLogger = nullptr;

            bool m_getCommandsFromSharedMemory = false;

            piga::Interface *m_pigaInterface = nullptr;
    };
}


#endif
