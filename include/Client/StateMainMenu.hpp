#ifndef CLIENT_STATEMAINMENU_HPP_INCLUDED
#define CLIENT_STATEMAINMENU_HPP_INCLUDED

#include <State.hpp>

#include <pihud/MenuContainer.hpp>
#include <pihud/PushButton.hpp>

#include <piga/GameEventHandler.hpp>
#include <SDLEventHandler.hpp>

#include <Client/BombermanMap.hpp>
#include <Client/EmbeddedTilemap.hpp>

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

            void addButton(std::shared_ptr<PiH::PushButton> button);

            void startGame(int playerID = 0);
            void quitGame(int playerID = 0);
            void customizeMap(int playerID = 0);
        private:
            PiH::MenuContainer *m_menuContainer = nullptr;
            EmbeddedTilemap *m_embeddedTilemap = nullptr;
            BombermanMap *m_mapCustomizer = nullptr;

            glm::vec2 m_mapOffset;
    };
}

#endif
