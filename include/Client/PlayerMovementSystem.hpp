#ifndef CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <map>
#include <Client/BombermanMap.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/BodyComponent.hpp>

namespace Client
{
    class PlayerMovementSystem : public anax::System<PlayerMovementSystem>
    {
        public:
            PlayerMovementSystem(BombermanMap *bombermanMap);
            virtual ~PlayerMovementSystem();

            void setMap(BombermanMap *map);

            void update(float frameTime);

            void onPlayerCollision(std::shared_ptr<Collision> collision);
        protected:
            virtual void onEntityRemoved(anax::Entity &e);
        private:
            BombermanMap *m_bombermanMap;
			std::map<anax::Entity::Id, sigc::connection> m_collisionConnections;
    };
}

#endif
