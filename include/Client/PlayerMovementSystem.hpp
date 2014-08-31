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
            PlayerMovementSystem(std::shared_ptr<BombermanMap> bombermanMap);
            virtual ~PlayerMovementSystem();

            void setMap(std::shared_ptr<BombermanMap> map);

            void update(float frameTime);
        private:
            std::shared_ptr<BombermanMap> m_bombermanMap;
    };
}

#endif
