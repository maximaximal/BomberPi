#ifndef CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/BombermanMap.hpp>

namespace Client
{
    class PlayerMovementSystem : public anax::System<PlayerMovementSystem>
    {
        public:
            PlayerMovementSystem(BombermanMap *bombermanMap);
            virtual ~PlayerMovementSystem();

            void setMap(BombermanMap *map);

            void update(float frameTime);
        private:
            BombermanMap *m_bombermanMap;
    };
}

#endif
