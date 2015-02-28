#ifndef CLIENT_STATEMAINMENU_HPP_INCLUDED
#define CLIENT_STATEMAINMENU_HPP_INCLUDED

#include <State.hpp>

#include <pihud/MenuContainer.hpp>

namespace Client
{
    class StateMainMenu : public State
    {
        public:
            StateMainMenu();
            virtual ~StateMainMenu();

            void init();

            virtual void render(Client::Window *window);
            virtual void update(float frametime);
        private:
			PiH::MenuContainer *m_menuContainer = nullptr;
    };
}

#endif
