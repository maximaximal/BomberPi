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
    class AIControlSystem;

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
            void setMapSize(const glm::ivec2 &size);

            void addPlayer(glm::ivec2 playerPos, piga::Player *pigaPlayer, int n);
        private:
            BombermanMap *m_map = nullptr;
			anax::World *m_world = nullptr;
			EntityFactory *m_entityFactory = nullptr;
            PlayerManager *m_playerManager = nullptr;
            WinChecker *m_winChecker = nullptr;

            glm::ivec2 m_offset;

            /**
             * @brief Calculates the position of the specified player on the map (in pixels).
             *
             * This function is only defined for the first 4 players. Every other player will spawn
             * in the middle of the map.
             *
             * @param The player to use for the calculation.
             * @return The position in pixels.
             */
            glm::ivec2 getPlayerPos(int playerID);

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
                HealthSystem *m_healthSystem = nullptr;
                KillEntityTypeSystem *m_killEntityTypeSystem = nullptr;
                AIControlSystem *m_AIControlSystem = nullptr;

    };
}

#endif
