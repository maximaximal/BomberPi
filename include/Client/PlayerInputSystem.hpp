#ifndef CLIENT_PLAYERINPUTSYSTEM_HPP
#define CLIENT_PLAYERINPUTSYSTEM_HPP

#include <map>
#include <sigc++/connection.h>
#include <anax/System.hpp>
#include <SDLEventHandler.hpp>
#include <Client/PlayerInputComponent.hpp>

namespace Client
{
    class PlayerInputSystem : public anax::System<PlayerInputSystem>
    {
      	public:
      		PlayerInputSystem();
            virtual ~PlayerInputSystem();

            void setSDLEventHandler(std::shared_ptr<SDLEventHandler> sdlEventHandler);

            void update();

            void onKeyDown(const SDL_Event &e, float frameTime);
            void onKeyUp(const SDL_Event &e, float frameTime);

            virtual void onEntityAdded(anax::Entity &entity);
            virtual void onEntityRemoved(anax::Entity &entity);
        private:
            std::shared_ptr<SDLEventHandler> m_sdlEventHandler;
            sigc::connection m_keyDownConnection;
            sigc::connection m_keyUpConnection;

            std::map<SDL_Scancode, PlayerInputComponent*> m_inputComponents;
    };
}

#endif
