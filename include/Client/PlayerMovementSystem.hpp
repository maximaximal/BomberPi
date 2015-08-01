#ifndef CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <map>
#include <Client/BombermanMap.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/CollisionSystem.hpp>

namespace Client
{
    class PositionComponent;

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
            void calculateTarget(PlayerInputEnum dir, BodyComponent &body, Client::PositionComponent &pos);
        private:
            BombermanMap *m_bombermanMap;
			std::map<anax::Entity::Id, sigc::connection> m_collisionConnections;
    };
}

#endif
