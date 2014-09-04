#ifndef CLIENT_STATEBOMBERMAN_HPP_INCLUDED
#define CLIENT_STATEBOMBERMAN_HPP_INCLUDED

#include <State.hpp>
#include <Client/Window.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/EntityFactory.hpp>
#include <anax/World.hpp>

namespace Client
{
    class SpriteRenderingSystem;
    class PlayerInputSystem;
    class PlayerMovementSystem;
    class TimerSystem;
    class BombPlaceSystem;

   	class StateBomberman : public State
    {
         public:
            StateBomberman();
            virtual ~StateBomberman();

            void init();

            virtual void update(float frameTime);

            virtual void render(std::shared_ptr<Window> window);
        private:
            std::shared_ptr<BombermanMap> m_map;
			std::shared_ptr<anax::World> m_world;
			std::shared_ptr<EntityFactory> m_entityFactory;

            //Systems
				std::shared_ptr<SpriteRenderingSystem> m_spriteRenderingSystem;
				std::shared_ptr<PlayerInputSystem> m_playerInputSystem;
				std::shared_ptr<PlayerMovementSystem> m_playerMovementSystem;
				std::shared_ptr<TimerSystem> m_timerSystem;
                std::shared_ptr<BombPlaceSystem> m_bombPlaceSystem;

    };
}

#endif
