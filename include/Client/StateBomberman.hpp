#ifndef CLIENT_STATEBOMBERMAN_HPP_INCLUDED
#define CLIENT_STATEBOMBERMAN_HPP_INCLUDED

#include <State.hpp>
#include <Client/Window.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/EntityFactory.hpp>
#include <Client/PlayerManager.hpp>
#include <Client/WinChecker.hpp>
#include <anax/World.hpp>

#include <pihud/HudContainer.hpp>
#include <pihud/HealthAndNameDisplay.hpp>

#include <piga/GameEventHandler.hpp>

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
    class HealthSystem;
    class KillEntityTypeSystem;

   	class StateBomberman : public State
    {
         public:
            StateBomberman();
            virtual ~StateBomberman();

            void init();

            virtual void update(float frameTime);

            virtual void render(Window *window);

            void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

            void startNewGame();

            void addPlayer(InputMap inputs, glm::ivec2 playerPos, const std::string &name);
        private:
            BombermanMap *m_map = nullptr;
			anax::World *m_world = nullptr;
			EntityFactory *m_entityFactory = nullptr;
            PlayerManager *m_playerManager = nullptr;
            WinChecker *m_winChecker = nullptr;

            glm::ivec2 m_offset;

            //Hud Components
				PiH::HudContainer *m_hudContainer = nullptr;

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
                HealthSystem *m_invincibleSystem = nullptr;
                KillEntityTypeSystem *m_killEntityTypeSystem = nullptr;

    };
}

#endif
