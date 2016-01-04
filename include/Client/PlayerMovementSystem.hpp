#ifndef CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_PLAYERMOVEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <map>
#include <Client/BombermanMap.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/CollisionSystem.hpp>

#include <Client/PositionComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <Client/SpeedComponent.hpp>

namespace Client
{
    class PositionComponent;

    class PlayerMovementSystem : public anax::System<anax::Requires<PositionComponent, PlayerInputComponent, SpriteComponent, BodyComponent, BombLayerComponent, SpeedComponent>>
    {
        public:
            PlayerMovementSystem(BombermanMap *bombermanMap, CollisionSystem *collisionSystem);
            virtual ~PlayerMovementSystem();

            void setMap(BombermanMap *map);

            void update(float frameTime);

            void onPlayerCollision(std::shared_ptr<Collision> collision);
        protected:
            virtual void onEntityRemoved(anax::Entity &e);
            void calculateTarget(PlayerInputEnum dir, BodyComponent &body, Client::PositionComponent &pos);
        private:
            BombermanMap *m_bombermanMap;
            CollisionSystem *m_collisionSystem;
			std::map<anax::Entity::Id, sigc::connection> m_collisionConnections;
    };
}

#endif
