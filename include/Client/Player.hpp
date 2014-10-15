#ifndef CLIENT_PLAYER_HPP_INCLUDED
#define CLIENT_PLAYER_HPP_INCLUDED

#include <string>
#include <anax/Entity.hpp>

namespace Client
{
    class Player
    {
        public:
            Player(const std::string &name, anax::Entity entity);
            virtual ~Player();

            void setEntity(anax::Entity playerEntity);
            void damageReceived(int damage, anax::Entity dealer);

            void die();
            bool isDead();
            int getHealth();
            void setHealth(int value);
        private:
            std::string m_name;
            anax::Entity m_entity;
    };
}

#endif
