#ifndef CLIENT_PLAYER_HPP_INCLUDED
#define CLIENT_PLAYER_HPP_INCLUDED

#include <string>
#include <anax/Entity.hpp>
#include <glm/vec2.hpp>
#include <piga/Player.hpp>

namespace Client
{
    namespace UI
    {
        class PowerupQueue;
    }
    class Player : public piga::Player
    {
        public:
            Player(const std::string &name, int playerID);
            virtual ~Player();

            void setEntity(anax::Entity playerEntity);
            void damageReceived(int damage, anax::Entity dealer);

            void die();
            bool isDead();
            int getHealth();
            void setHealth(int value);
            void setPosition(const glm::ivec2 &pos);
            void resetBombLayerComponent();
            const glm::ivec2& getStartingPosition();
            glm::ivec2 getPosition();
            void setPowerupQueueUI(UI::PowerupQueue *powerupQueueUI);

            void update(float frametime);
            void reset();
        private:
            anax::Entity m_entity;
    };
}

#endif
