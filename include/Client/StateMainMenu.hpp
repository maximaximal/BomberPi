#ifndef CLIENT_STATEMAINMENU_HPP_INCLUDED
#define CLIENT_STATEMAINMENU_HPP_INCLUDED

#include <State.hpp>

#include <pihud/MenuContainer.hpp>

#include <piga/GameEventHandler.hpp>
#include <SDLEventHandler.hpp>

namespace Client
{
    class StateMainMenu : public State, public piga::GameEventHandler, public SDLEventHandler
    {
        public:
            StateMainMenu();
            virtual ~StateMainMenu();

            void init();

            virtual void render(Client::Window *window);
            virtual void update(float frametime);
        protected:
            virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);
			virtual void onSDLEvent(const SDL_Event &e, float frametime);

            void startGame(int playerID = 0);
        private:
			PiH::MenuContainer *m_menuContainer = nullptr;
    };
}

#endif
