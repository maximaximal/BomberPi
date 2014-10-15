#ifndef CLIENT_PLAYER_HPP_INCLUDED
#define CLIENT_PLAYER_HPP_INCLUDED

#include <string>
#include <anax/Entity.hpp>
#include <glm/vec2.hpp>

namespace Client
{
    class Player
    {
        public:
            Player(const std::string &name);
            virtual ~Player();

            void setEntity(anax::Entity playerEntity);
            void damageReceived(int damage, anax::Entity dealer);

            void die();
            bool isDead();
            int getHealth();
            const std::string& getName();
            void setHealth(int value);
            void setPosition(const glm::ivec2 &pos);
            const glm::ivec2& getStartingPosition();
            glm::ivec2 getPosition();

            void update(float frametime);
            void reset();
        private:
            std::string m_name;
            anax::Entity m_entity;
    };
}

#endif
