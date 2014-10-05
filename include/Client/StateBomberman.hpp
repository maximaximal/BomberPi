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
    class BombPlacePositionSystem;
    class AnimationSystem;
    class BombExplodeSystem;
    class ExplosionSystem;
    class ExplosionManagementSystem;
    class CollisionSystem;
    class DamageSystem;

   	class StateBomberman : public State
    {
         public:
            StateBomberman();
            virtual ~StateBomberman();

            void init();

            virtual void update(float frameTime);

            virtual void render(Window *window);
        private:
            BombermanMap *m_map = nullptr;
			anax::World *m_world = nullptr;
			EntityFactory *m_entityFactory = nullptr;

            //Systems
				SpriteRenderingSystem *m_spriteRenderingSystem = nullptr;
				PlayerInputSystem *m_playerInputSystem = nullptr;
				PlayerMovementSystem *m_playerMovementSystem = nullptr;
				TimerSystem *m_timerSystem = nullptr;
                BombPlaceSystem *m_bombPlaceSystem = nullptr;
                BombPlacePositionSystem *m_bombPlacePositionSystem = nullptr;
                AnimationSystem *m_animationSystem = nullptr;
                BombExplodeSystem *m_bombExplodeSystem = nullptr;
                ExplosionSystem *m_explosionSystem = nullptr;
                ExplosionManagementSystem *m_explosionManagementSystem = nullptr;
                CollisionSystem *m_collisionSystem = nullptr;
                DamageSystem *m_damageSystem = nullptr;

    };
}

#endif
