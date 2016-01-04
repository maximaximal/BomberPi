#ifndef CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
#define CLIENT_COLLISIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/Collision.hpp>

#include <Client/PositionComponent.hpp>
#include <Client/BodyComponent.hpp>

namespace Client
{
    class CollisionSystem : public anax::System<anax::Requires<PositionComponent, BodyComponent>>
    {
        public:
            CollisionSystem(BombermanMap *bombermanMap);
            virtual ~CollisionSystem();

            void update(float frametime);
            void collideWithMapTile(uint8_t collision, const glm::ivec2 &tile, anax::Entity &e);

            anax::Entity getEntityAt(const glm::ivec2 &pos, bool &entityFound);
        private:
            BombermanMap *m_map;
    };
}

#endif // CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
