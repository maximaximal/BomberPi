#ifndef CLIENT_PLAYERINPUTSYSTEM_HPP
#define CLIENT_PLAYERINPUTSYSTEM_HPP

#include <map>
#include <sigc++/connection.h>
#include <anax/System.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <piga/GameEventHandler.hpp>

namespace Client
{
    class PlayerInputSystem : public anax::System<PlayerInputSystem>
    {
      	public:
      		PlayerInputSystem();
            virtual ~PlayerInputSystem();

            void setGameEventHandler(std::shared_ptr<piga::GameEventHandler> gameEventHandler);

            void update();

            void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

            virtual void onEntityAdded(anax::Entity &entity);
            virtual void onEntityRemoved(anax::Entity &entity);

            static PlayerInputEnum getPlayerInputEnumFromPigaGameControl(piga::GameControl control);
            static piga::GameControl getPigaGameControlFromPlayerInputEnum(PlayerInputEnum playerInput);
        private:
            std::shared_ptr<piga::GameEventHandler> m_gameEventHandler;
            sigc::connection m_gameEventConnection;

            std::map<int, PlayerInputComponent*> m_inputComponents;
    };
}

#endif
